#include <iostream>
#include <signal.h>
#include <string>
#include <syslog.h>
#include <unistd.h>

#include "version.h"

#include "daemon.h"
#include "http.h"
#include "hv/hlog.h"

static void exitHandle(int signo) {
    stopDaemon();
    deinitHttpd();
    stopWifi();
    closelog();

    exit(0);
}

static void initSupervisor() {
    hlog_disable();
    openlog("supervisor", LOG_CONS | LOG_PERROR, LOG_DAEMON);

    initWiFi();
    initHttpd();
    initDaemon();

    signal(SIGINT, &exitHandle);
    signal(SIGTERM, &exitHandle);

    setlogmask(LOG_UPTO(LOG_NOTICE));
}

int main(int argc, char** argv) {

    printf("Build Time: %s %s\n", __DATE__, __TIME__);
    if (argc > 1 && std::string(argv[1]) == "-v") {
        printf("Version: %s\n", PROJECT_VERSION);
    }

    initSupervisor();

    while (1)
        sleep(1000);

    system(SCRIPT_WIFI_STOP);
    deinitHttpd();

    closelog();

    return 0;
}
