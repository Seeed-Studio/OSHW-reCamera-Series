#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <time.h>

#include "daemon.h"
#include "global_cfg.h"
#include "hv/hv.h"
#include "hv/mqtt_client.h"
#include "hv/requests.h"

#define MQTT_TOPIC_IN  "sscma/v0/recamera/node/in/"
#define MQTT_TOPIC_OUT "sscma/v0/recamera/node/out/"
#define MQTT_PAYLOAD   "{\"name\":\"health\",\"type\":3,\"data\":\"\"}"

const int threadTimeout  = 3;
const int retryTimes     = 3;
int daemonStatus         = 0;
int noderedStarting      = 1;
int sscmaStarting        = 1;
APP_STATUS noderedStatus = APP_STATUS_UNKNOWN;
APP_STATUS sscmaStatus   = APP_STATUS_UNKNOWN;
sem_t semSscma;

hv::MqttClient cli;

void runMqtt() {
    cli.run();
}

void initMqtt() {
    sem_init(&semSscma, 0, 0);

    cli.onConnect = [](hv::MqttClient* cli) {
        cli->subscribe(MQTT_TOPIC_OUT);
        cli->publish(MQTT_TOPIC_IN, MQTT_PAYLOAD);
    };

    cli.onMessage = [](hv::MqttClient* cli, mqtt_message_t* msg) {
        sem_post(&semSscma);
    };

    cli.onClose = [](hv::MqttClient* cli) {
        syslog(LOG_INFO, "mqtt disconnected");
    };

    cli.setPingInterval(10);
    cli.setID("supervisor");
    cli.connect("localhost", 1883, 0);

    std::thread th(runMqtt);
    th.detach();
}

int startFlow() {
    hv::Json data;
    http_headers headers;

    data["state"]           = "start";
    headers["Content-Type"] = "application/json";

    auto resp = requests::post("localhost:1880/flows/state", data.dump(), headers);
    if (resp == NULL) {
        syslog(LOG_ERR, "stop flow failed");
        return -1;
    }

    return 0;
}

int stopFlow() {
    hv::Json data;
    http_headers headers;

    data["state"]           = "stop";
    headers["Content-Type"] = "application/json";

    auto resp = requests::post("localhost:1880/flows/state", data.dump(), headers);
    if (resp == NULL) {
        syslog(LOG_ERR, "stop flow failed");
        return -1;
    }

    return 0;
}

int startApp(const char* cmd, const char* appName) {
    FILE* fp;
    char info[128] = "";
    int len        = 0;

    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return -1;
    }

    fgets(info, sizeof(info) - 1, fp);
    len = strlen(info);
    if (info[len - 1] == '\n') {
        info[len - 1] = '\0';
    }
    pclose(fp);
    syslog(LOG_INFO, "%s status: %s\n", appName, info);

    if (0 != strcmp(info, "Finished")) {
        return -1;
    }

    return 0;
}

APP_STATUS getFlowStatus() {
    auto resp = requests::get("localhost:1880/flows/state");

    if (resp == NULL) {
        return APP_STATUS_NORESPONSE;
    } else {
        try {
            hv::Json data = hv::Json::parse(resp->body.begin(), resp->body.end());

            if (data["state"] == "stop") {
                return APP_STATUS_STOP;
            }
        } catch (const std::exception& e) {
            return APP_STATUS_NORESPONSE;
        }
    }

    return APP_STATUS_NORMAL;
}

APP_STATUS getNoderedStatus() {
    for (int i = 0; i < retryTimes; i++) {
        auto resp = requests::get("localhost:1880");

        if (NULL != resp) {
            return getFlowStatus();
        }

        std::this_thread::sleep_for(std::chrono::seconds(threadTimeout));
    }

    return APP_STATUS_NORESPONSE;
}

APP_STATUS getSscmaStatus() {
    struct timespec ts;

    if (!cli.isConnected()) {
        syslog(LOG_ERR, "mqtt is not connected\n");
        cli.reconnect();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = 0; i < retryTimes; i++) {
        cli.publish(MQTT_TOPIC_IN, MQTT_PAYLOAD);

        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_nsec += 500 * 1000;
        if (0 == sem_timedwait(&semSscma, &ts)) {
            return APP_STATUS_NORMAL;
        }

        std::this_thread::sleep_for(std::chrono::seconds(threadTimeout));
    }

    return APP_STATUS_NORESPONSE;
}

void runDaemon() {
    initMqtt();

    while (daemonStatus) {
        std::this_thread::sleep_for(std::chrono::seconds(threadTimeout));
        APP_STATUS appStatus;

        appStatus = getNoderedStatus();
        if (APP_STATUS_NORMAL == appStatus) {
            if (noderedStarting) {
                noderedStarting = 0;
                syslog(LOG_INFO, "node-red startup status: Finished\n");
            }

            if (APP_STATUS_NORESPONSE == noderedStatus) {
                syslog(LOG_INFO, "Stop Flow");
                stopFlow();
                noderedStatus = APP_STATUS_STOP;
            } else {
                noderedStatus = APP_STATUS_NORMAL;
            }
        } else if (APP_STATUS_NORESPONSE == appStatus) {
            if (noderedStarting) {
                syslog(LOG_INFO, "Nodered is starting");
            } else {
                syslog(LOG_ERR, "node-red is not responding");
                if (0 != startApp(SCRIPT_DEVICE_RESTARTNODERED, "node-red")) {
                    noderedStatus   = APP_STATUS_STARTFAILED;
                    noderedStarting = 0;
                } else {
                    noderedStarting = 1;
                    startApp(SCRIPT_DEVICE_RESTARTSSCMA, "sscma-node");
                    sscmaStarting = 1;
                }
            }
        } else {
            if (noderedStarting) {
                noderedStarting = 0;
            }
            noderedStatus = appStatus;
        }

        appStatus = getSscmaStatus();
        if (APP_STATUS_NORMAL == appStatus) {
            if (sscmaStarting) {
                sscmaStarting = 0;
            }
            if (APP_STATUS_NORESPONSE == sscmaStatus) {
                syslog(LOG_INFO, "Restart Flow");
                startFlow();
            }
            sscmaStatus = appStatus;
        } else {
            if (sscmaStarting) {
                continue;
            }
            sscmaStatus = appStatus;
            syslog(LOG_ERR, "sscma-node is not responding");
            stopFlow();
            if (0 != startApp(SCRIPT_DEVICE_RESTARTSSCMA, "sscma-node")) {
                sscmaStatus   = APP_STATUS_STARTFAILED;
                sscmaStarting = 0;
            } else {
                sscmaStarting = 1;
            }
        }
    }
}

void initDaemon() {
    std::thread th;

    daemonStatus = 1;
    th           = std::thread(runDaemon);
    th.detach();
}

void stopDaemon() {
    daemonStatus = 0;
}
