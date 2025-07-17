#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>

#include "common.h"
#include "daemon.h"
#include "global_cfg.h"
#include "hv/HttpServer.h"
#include "utils_device.h"

SERVICE_STATUS systemStatus = SERVICE_STATUS_STARTING;
std::string sn;
std::string ip;
bool g_updateStatus = true;
int g_progress      = 0;
int g_restart       = 0;

SERVICE_STATUS convertStatus(APP_STATUS appStatus) {
    switch (appStatus) {
        case APP_STATUS_NORMAL:
            return SERVICE_STATUS_NORMAL;

        case APP_STATUS_STOP:
            return SERVICE_STATUS_NORMAL;

        case APP_STATUS_NORESPONSE:
            return SERVICE_STATUS_ERROR;

        case APP_STATUS_STARTFAILED:
            return SERVICE_STATUS_STARTFAILED;
    }

    return SERVICE_STATUS_ERROR;
}

std::string readFile(const std::string& path, const std::string& defaultname) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        // 文件无法打开，返回默认值
        return defaultname;
    }
    // 读取文件内容并返回
    return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}

static int writeFile(const std::string& path, const std::string& strWrite) {
    std::ofstream outfile(path);
    if (outfile.is_open()) {
        outfile << strWrite;
        outfile.close();
        syslog(LOG_DEBUG, "Write Success: %s\n", path.c_str());
        return 0;
    }

    return -1;
}

static void clearNewline(char* value, int len) {
    if (value[len - 1] == '\n') {
        value[len - 1] = '\0';
    }
}

static void clearNewline(std::string& value) {
    if (value.back() == '\n') {
        value.erase(value.size() - 1);
    }
}

int createFolder(const char* dirName) {
    struct stat dirStat;
    mode_t mode = 0755;

    if (stat(dirName, &dirStat) != 0) {
        if (mkdir(dirName, mode) != 0) {
            syslog(LOG_DEBUG, "Failed to create %s folder\n", dirName);
            return -1;
        }
    }

    return 0;
}

static int saveModelFile(const HttpContextPtr& ctx, std::string filePath) {
    const char* modelKey = "model_file";
    auto form            = ctx->request->GetForm();
    HFile file;

    if (form.empty()) {
        return HTTP_STATUS_BAD_REQUEST;
    }

    auto iter = form.find(modelKey);
    if (iter == form.end()) {
        return 200;
    }

    const auto& formdata = iter->second;
    if (formdata.content.empty()) {
        return HTTP_STATUS_BAD_REQUEST;
    }

    filePath += "model.cvimodel";
    if (file.open(filePath.c_str(), "wb") != 0) {
        return HTTP_STATUS_INTERNAL_SERVER_ERROR;
    }
    file.write(formdata.content.data(), formdata.content.size());

    return 200;
}

static int saveModelInfoFile(const HttpContextPtr& ctx, std::string filePath) {
    const char* modelKey  = "model_info";
    std::string modelInfo = ctx->request->GetFormData(modelKey);
    HFile file;

    filePath += "model.json";
    if (file.open(filePath.c_str(), "wb") != 0) {
        syslog(LOG_DEBUG, "open %s file failed\n", filePath.c_str());
        return HTTP_STATUS_INTERNAL_SERVER_ERROR;
    } else {
        file.write(modelInfo.c_str(), modelInfo.size());
    }

    return 200;
}

static std::string getFileMd5(std::string filePath) {
    FILE* fp;
    char cmd[128]      = SCRIPT_DEVICE_GETFILEMD5;
    char md5Value[128] = "";

    strcat(cmd, filePath.c_str());
    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return std::string(md5Value);
    }

    fgets(md5Value, sizeof(md5Value) - 1, fp);
    clearNewline(md5Value, strlen(md5Value));
    pclose(fp);

    return std::string(md5Value);
}

static std::string getDeviceIp(std::string clientIp) {
    FILE* fp;
    char cmd[128]      = SCRIPT_DEVICE_GETADDRESSS;
    char deviceIp[128] = "";

    strcat(cmd, clientIp.c_str());
    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return std::string(deviceIp);
    }

    fgets(deviceIp, sizeof(deviceIp) - 1, fp);
    clearNewline(deviceIp, strlen(deviceIp));
    pclose(fp);

    return std::string(deviceIp);
}

void initSystemStatus() {
    FILE* fp;
    char cmd[128]  = SCRIPT_DEVICE_GETSYSTEMSTATUS;
    char info[128] = "";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        systemStatus = SERVICE_STATUS_ERROR;
        return;
    }

    fgets(info, sizeof(info) - 1, fp);
    clearNewline(info, strlen(info));

    if (strlen(info) == 0) {
        systemStatus = SERVICE_STATUS_NORMAL;
    } else {
        systemStatus = SERVICE_STATUS_ERROR;
    }

    pclose(fp);
}

void getSnCode() {
    FILE* fp;
    char cmd[128]  = SCRIPT_DEVICE_GETSNCODE;
    char info[128] = "";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return;
    }

    fgets(info, sizeof(info) - 1, fp);
    clearNewline(info, strlen(info));

    sn = std::string(info);

    pclose(fp);
}

std::string getChannelUrl() {
    std::string info = "";
    size_t pos       = 0;

    info = readFile(PATH_UPGRADE_URL);
    clearNewline(info);

    if (info[0] == '0') {
        return std::string(DEFAULT_UPGRADE_URL);
    }

    pos = info.find(',');
    if (pos == std::string::npos) {
        return std::string("");
    }

    return info.substr(pos + 1);
}

bool needUpdateSystem() {
    FILE* fp;
    char cmd[128]  = SCRIPT_UPGRADE_LATEST;
    char info[128] = "";

    strcat(cmd, getChannelUrl().c_str());
    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return false;
    }

    fgets(info, sizeof(info) - 1, fp);
    clearNewline(info, strlen(info));

    pclose(fp);

    if (strstr(info, "YES") != NULL) {
        return true;
    }

    return false;
}

bool downloadFirmware() {
    FILE* fp;
    char cmd[128]  = SCRIPT_UPGRADE_DOWNLOAD;
    char info[128] = "";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return false;
    }

    fgets(info, sizeof(info) - 1, fp);
    clearNewline(info, strlen(info));

    pclose(fp);

    if (strstr(info, "OK") != NULL) {
        return true;
    }

    return true;
}

int getUpdateStatus() {
    FILE* fp;
    char cmd[128]  = SCRIPT_DEVICE_GETUPDATESTATUS;
    char info[128] = "";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return -1;
    }

    fgets(info, sizeof(info) - 1, fp);
    clearNewline(info, strlen(info));
    pclose(fp);

    if (strcmp(info, "YES") == 0) {
        return 1;
    }

    return 0;
}

void updateSystemThread() {
    while (g_updateStatus) {
        if (needUpdateSystem()) {
            downloadFirmware();
        }

        std::this_thread::sleep_for(std::chrono::seconds(120));
    }
}

int getSystemStatus(HttpRequest* req, HttpResponse* resp) {
    FILE* fp;
    char cmd[128]  = SCRIPT_DEVICE_GETSYSTEMSTATUS;
    char info[128] = "";
    hv::Json response;

    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        response["code"] = -1;
        response["msg"]  = "Failed to run " + std::string(cmd);
        response["data"] = hv::Json({});
        return resp->Json(response);
    }

    fgets(info, sizeof(info) - 1, fp);
    clearNewline(info, strlen(info));

    if (strlen(info) == 0) {
        response["code"] = 0;
        response["msg"]  = "";
    } else {
        response["code"] = -1;
        response["msg"]  = "System damage";
    }

    pclose(fp);

    response["data"] = hv::Json({});

    return resp->Json(response);
}

int queryServiceStatus(HttpRequest* req, HttpResponse* resp) {
    hv::Json response;

    response["code"]              = 0;
    response["msg"]               = "";
    response["data"]["sscmaNode"] = sscmaStarting ? SERVICE_STATUS_STARTING : convertStatus(sscmaStatus);
    response["data"]["nodeRed"]   = noderedStarting ? SERVICE_STATUS_STARTING : convertStatus(noderedStatus);
    response["data"]["system"]    = systemStatus;
    response["data"]["uptime"]    = getUptime();
    response["data"]["timestamp"] = getTimestamp();

    return resp->Json(response);
}

int getSystemUpdateVesionInfo(HttpRequest* req, HttpResponse* resp) {
    syslog(LOG_INFO, "start to get SystemUpdateVersinInfo...\n");

    hv::Json response;
    FILE* fp;
    char cmd[128] = SCRIPT_UPGRADE_LATEST, info[128] = "";
    std::string content = "", os = "Null", version = "Null";
    size_t pos       = 0;
    int updateStatus = getUpdateStatus();
    bool error       = false;

    if (updateStatus) {
        response["code"]                = 0;
        response["msg"]                 = "The system is being upgraded";
        response["data"]["osName"]      = os;
        response["data"]["osVersion"]   = version;
        response["data"]["downloadUrl"] = "";
        response["data"]["isUpgrading"] = updateStatus;
        return resp->Json(response);
    }

    strcat(cmd, getChannelUrl().c_str());
    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        error = true;
    }

    if (!error) {
        fgets(info, sizeof(info) - 1, fp);
        clearNewline(info, strlen(info));
        pclose(fp);

        content = readFile(PATH_UPGRADE_VERSION_FILE, "");
        clearNewline(content);
        pos = content.find(' ');

        if (strstr(info, "Failed") != NULL || content == "" || pos == std::string::npos) {
            error = true;
        }
    }

    if (error) {
        response["code"]                = -1;
        response["msg"]                 = "Failed to get system version information";
        response["data"]["osName"]      = os;
        response["data"]["osVersion"]   = version;
        response["data"]["downloadUrl"] = "";
        response["data"]["isUpgrading"] = updateStatus;
        return resp->Json(response);
    }

    os      = content.substr(0, pos);
    version = content.substr(pos + 1);

    syslog(LOG_DEBUG, "content: %s\n", content.c_str());
    syslog(LOG_DEBUG, "os: %s, version: %s\n", os.c_str(), version.c_str());

    response["code"]                = 0;
    response["msg"]                 = "Get system version information successfully";
    response["data"]["osName"]      = os;
    response["data"]["osVersion"]   = version;
    response["data"]["downloadUrl"] = "";
    response["data"]["isUpgrading"] = updateStatus;

    return resp->Json(response);
}

int queryDeviceInfo(HttpRequest* req, HttpResponse* resp) {
    hv::Json device;
    device["code"] = 0;
    device["msg"]  = "";

    std::string wifiStatus;
    std::string os_version = readFile(PATH_ISSUE);
    std::string os = "Null", version = "Null";
    size_t pos = os_version.find(' ');
    if (pos != std::string::npos) {
        os      = os_version.substr(0, pos);
        version = os_version.substr(pos + 1);
    }
    if (version.back() == '\n') {
        version.erase(version.size() - 1);
    }

    std::string ch_url = readFile(PATH_UPGRADE_URL);
    std::string ch = "0", url = "";
    pos = ch_url.find(',');
    if (pos != std::string::npos) {
        ch  = ch_url.substr(0, pos);
        url = ch_url.substr(pos + 1);
    }
    if (url.back() == '\n') {
        url.erase(url.size() - 1);
    }

    wifiStatus = getWifiConnectStatus();

    hv::Json data;
    data["appName"]    = "supervisor";
    data["deviceName"] = readFile(PATH_DEVICE_NAME);
    data["sn"]         = sn;
    data["ip"]         = getDeviceIp(req->client_addr.ip);

    if (wifiStatus == "COMPLETED" && isLegalWifiIp()) {
        data["wifiIp"]  = getIpAddress("wlan0");
        data["mask"]    = getNetmaskAddress("wlan0");
        data["gateway"] = getGateWay(data["wifiIp"]);
    } else {
        data["wifiIp"]  = "-";
        data["mask"]    = "-";
        data["gateway"] = "-";
    }

    data["dns"]          = "-";
    data["channel"]      = std::stoi(ch);
    data["serverUrl"]    = url;
    data["officialUrl"]  = DEFAULT_UPGRADE_URL;
    data["cpu"]          = "sg2002";
    data["ram"]          = 256;
    data["npu"]          = 1;
    data["osName"]       = os;
    data["osVersion"]    = version;
    data["osUpdateTime"] = "2024.01.01";
    data["terminalPort"] = TTYD_PORT;
    data["needRestart"]  = g_restart;

    device["data"] = data;

    // output
    syslog(LOG_INFO, "Device name: %s\n", data["deviceName"].template get<std::string>().c_str());
    syslog(LOG_INFO, "OS,Version: %s\n", os_version.c_str());
    syslog(LOG_INFO, "Channel,Url: %s\n", ch_url.c_str());

    return resp->Json(device);
}

int updateDeviceName(HttpRequest* req, HttpResponse* resp) {
    std::string dev_name = req->GetString("deviceName");

    syslog(LOG_INFO, "update Device Name operation...\n");
    syslog(LOG_INFO, "deviceName: %s\n", dev_name.c_str());

    writeFile(PATH_DEVICE_NAME, dev_name);

    hv::Json response;
    response["code"] = 0;
    response["msg"]  = "";
    response["data"] = hv::Json({});

    // sync ap name
    // system(("sed -i s/^ssid=.*/ssid=" + dev_name + "/ " PATH_HOSTAPD_CONF).c_str());

    // sync nodered name
    system(("sed -i 's/\\(username: \\)\"[^\"]*\"/\\1\"" + dev_name + "\"/' " + PATH_NODERED_CONF).c_str());
    system("sync");

    // rebroadcast device name
    system(("sed -i s/^host-name=.*/host-name=" + dev_name + "/ " PATH_AVAHI_CONF).c_str());
    system("sync");
    system(PATH_AVAHI_DAEMON_SERVICE " stop");
    hv_msleep(100);
    system(PATH_AVAHI_DAEMON_SERVICE " start");


    return resp->Json(response);
}

int updateChannel(HttpRequest* req, HttpResponse* resp) {
    hv::Json response;
    std::string str_ch  = req->GetString("channel");
    std::string str_url = req->GetString("serverUrl");
    std::string str_cmd;

    syslog(LOG_INFO, "update channel operation...\n");
    syslog(LOG_INFO, "channel: %s\n", str_ch.c_str());
    syslog(LOG_INFO, "serverUrl: %s\n", str_url.c_str());

    if (getUpdateStatus()) {
        response["code"] = -1;
        response["msg"]  = "Upgrading, this operation is prohibited";
        response["data"] = hv::Json({});

        return resp->Json(response);
    }

    if (str_ch[0] == '1') {
        bool error = false;
        if (str_url.compare(0, 7, "http://") != 0 && str_url.compare(0, 8, "https://") != 0) {
            error = true;
        }

        if (str_url.size() >= 6 && str_url.compare(str_url.size() - 6, 6, "latest") != 0) {
            error = true;
        }

        if (error && str_url.size()) {
            response["code"] = -1;
            response["msg"]  = "Invalid Address";
            response["data"] = hv::Json({});

            return resp->Json(response);
        }
    }

    if (str_ch.empty()) {
        response["code"] = 1109;
        response["msg"]  = "value error";
        response["data"] = hv::Json({});

        return resp->Json(response);
    }

    if (str_ch.compare("0") == 0) {
        str_cmd = "sed -i \"s/1,/0,/g\" ";
        str_cmd += PATH_UPGRADE_URL;
    } else {
        str_cmd = "echo " + str_ch + "," + str_url + " > ";
        str_cmd += PATH_UPGRADE_URL;
    }

    system(str_cmd.c_str());
    system("sync");

    response["code"] = 0;
    response["msg"]  = "";
    response["data"] = hv::Json({});

    return resp->Json(response);
}

int setPower(HttpRequest* req, HttpResponse* resp) {
    syslog(LOG_INFO, "set Power operation...\n");
    syslog(LOG_INFO, "mode: %s\n", req->GetString("mode").c_str());

    int mode = stoi(req->GetString("mode"));

    if (mode) {
        syslog(LOG_INFO, "start to reboot system\n");
        system("reboot");
    } else {
        syslog(LOG_INFO, "start to shut down system\n");
        system("poweroff");
    }

    hv::Json response;

    response["code"] = 0;
    response["msg"]  = "";
    response["data"] = hv::Json({});

    return resp->Json(response);
}

/* upgrade */
int updateSystem(HttpRequest* req, HttpResponse* resp) {
    syslog(LOG_INFO, "start to update System now...\n");

    char cmd[128] = SCRIPT_UPGRADE_START;

    stopFlow();

    strcat(cmd, "&");
    system(cmd);

    hv::Json response;

    response["code"] = 0;
    response["msg"]  = "";
    response["data"] = hv::Json({});

    return resp->Json(response);
}

int getUpdateProgress(HttpRequest* req, HttpResponse* resp) {
    syslog(LOG_INFO, "get Update Progress...\n");

    FILE* fp;
    char info[128];
    hv::Json response, data;

    fp = popen(SCRIPT_UPGRADE_QUERY, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", SCRIPT_UPGRADE_QUERY, strerror(errno));
        return -1;
    }

    while (fgets(info, sizeof(info) - 1, fp) != NULL) {
        std::string s(info);
        if (s.back() == '\n') {
            s.erase(s.size() - 1);
        }

        syslog(LOG_INFO, "info: %s\n", s.c_str());
        size_t pos = s.find(',');
        if (pos != std::string::npos) {
            g_progress       = stoi(s.substr(0, pos));
            response["code"] = 1106;
            response["msg"]  = s.substr(pos + 1, s.size() - 1);
        } else {
            g_progress       = stoi(s);
            response["code"] = 0;
            response["msg"]  = "";
        }
    }

    pclose(fp);

    if (g_progress == 100) {
        g_restart = 1;
    }

    data["progress"] = g_progress;
    response["data"] = data;

    return resp->Json(response);
}

int cancelUpdate(HttpRequest* req, HttpResponse* resp) {
    syslog(LOG_INFO, "cancel update...\n");

    system(SCRIPT_UPGRADE_STOP);

    hv::Json response;

    response["code"] = 0;
    response["msg"]  = "";
    response["data"] = hv::Json({});

    return resp->Json(response);
}

std::vector<std::string> parse_line(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ';')) {
        fields.push_back(field);
    }
    return fields;
}

// need async
int getDeviceList(HttpRequest* req, HttpResponse* resp) {
    const char* cmd = "timeout 15 avahi-browse -arpt";
    hv::Json response;
    hv::Json data = hv::Json::array();

    std::array<char, 256> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), fclose);
    if (!pipe) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return -1;
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    std::map<std::pair<std::string, std::string>, std::map<std::string, std::string>> devices_services;

    std::stringstream ss(result);
    std::string line;

    while (std::getline(ss, line)) {
        auto fields = parse_line(line);

        if (fields.size() > 8 && fields[0] == "=") {
            std::string device_name  = fields[3];
            std::string service_name = fields[4];
            std::string ip           = fields[7];
            std::string port         = fields[8];
            std::string type         = fields[1];

            devices_services[{device_name, ip}][service_name] = port;
            devices_services[{device_name, ip}]["type"]       = type;
            if (fields.size() > 9 && service_name == "_sscma._tcp") {
                devices_services[{device_name, ip}]["info"] = fields[9];  // extra info
            }
        }
    }

    for (const auto& device : devices_services) {

        if (device.second.find("_sscma._tcp") == device.second.end() || device.second.find("_ws._tcp") == device.second.end()) {
            continue;
        }

        hv::Json device_json;
        const auto& device_name = device.first.first;
        const auto& device_ip   = device.first.second;
        const auto& device_type = device.second.at("type");

        device_json["device"] = device_name;
        device_json["ip"]     = device_ip;
        device_json["type"]   = device_type;
        if (device.second.find("info") != device.second.end()) {
            device_json["info"] = device.second.at("info");
        }

        hv::Json services = hv::Json::object();

        for (const auto& service : device.second) {
            if (service.first != "type" && service.first != "info") {
                services[service.first] = service.second;
            }
        }

        device_json["services"] = services;
        data.push_back(device_json);
    }

    response["code"] = 0;
    response["mgs"]  = "";

    response["data"]["deviceList"] = data;

    return resp->Json(response);
}

int getDeviceInfo(HttpRequest* req, HttpResponse* resp) {
    hv::Json response, data;
    std::string os_version = readFile(PATH_ISSUE);
    std::string os = "Null", version = "Null";
    size_t pos;

    clearNewline(os_version);
    pos = os_version.find(' ');
    if (pos != std::string::npos) {
        os      = os_version.substr(0, pos);
        version = os_version.substr(pos + 1);
    }

    data["deviceName"] = os;
    data["ip"]         = getDeviceIp(req->client_addr.ip);
    data["status"]     = 1;
    data["osVersion"]  = version;
    data["sn"]         = sn;

    response["code"] = 0;
    response["mgs"]  = "";
    response["data"] = data;

    return resp->Json(response);
}

int getAppInfo(HttpRequest* req, HttpResponse* resp) {
    FILE* fp;
    char cmd[128]    = SCRIPT_DEVICE_GETAPPINFO;
    char appName[20] = "", appVersion[10] = "";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return -1;
    }

    fgets(appName, sizeof(appName) - 1, fp);
    clearNewline(appName, strlen(appName));

    fgets(appVersion, sizeof(appVersion) - 1, fp);
    clearNewline(appVersion, strlen(appVersion));

    hv::Json response;
    response["code"]               = 0;
    response["msg"]                = "";
    response["data"]["appName"]    = appName;
    response["data"]["appVersion"] = appVersion;

    pclose(fp);

    return resp->Json(response);
}

int uploadApp(const HttpContextPtr& ctx) {
    int ret             = 0;
    std::string appPath = PATH_APP_DOWNLOAD_DIR;
    FILE* fp;
    char cmd[128]  = SCRIPT_DEVICE_INSTALLAPP;
    char info[128] = "";

    if (ctx->param("filename").empty()) {
        syslog(LOG_ERR, "Missing filename parameter value\n");
    }

    if (ctx->is(MULTIPART_FORM_DATA)) {
        ret = ctx->request->SaveFormFile("file", appPath.c_str());
    } else {
        std::string fileName = ctx->param("filename", "app.zip");
        std::string filePath = appPath + fileName;
        ret                  = ctx->request->SaveFile(filePath.c_str());
    }

    strcat(cmd, std::string(appPath + ctx->param("filename")).c_str());
    strcat(cmd, " ");
    strcat(cmd, ctx->param("appName").c_str());
    strcat(cmd, " ");
    strcat(cmd, ctx->param("appVersion").c_str());
    fp = popen(cmd, "r");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to run `%s`(%s)\n", cmd, strerror(errno));
        return -1;
    }

    fgets(info, sizeof(info) - 1, fp);
    clearNewline(info, strlen(info));

    syslog(LOG_INFO, "info: %s\n", info);

    hv::Json response;
    if (strcmp(info, "Finished") == 0) {
        response["code"] = 0;
        response["msg"]  = "";
    } else {
        response["code"] = -1;
        response["msg"]  = info;
    }
    response["data"] = hv::Json({});

    pclose(fp);

    ctx->response.get()->Set("code", 200);
    ctx->response.get()->Set("message", response.dump(2));
    return 200;
}

int getModelInfo(HttpRequest* req, HttpResponse* resp) {
    std::string modelInfo;
    std::string filePath      = PATH_MODEL_DOWNLOAD_DIR + std::string("model.json");
    std::string modelFilePath = PATH_MODEL_DOWNLOAD_DIR + std::string("model.cvimodel");
    hv::Json response;

    modelInfo = readFile(filePath, "NULL");

    if (modelInfo == "NULL") {
        response["code"] = -1;
        response["msg"]  = "File does not exist";
        response["data"] = hv::Json({});
    } else {
        response["code"]               = 0;
        response["msg"]                = "";
        response["data"]["model_info"] = modelInfo;
        response["data"]["model_md5"]  = getFileMd5(modelFilePath);
    }

    return resp->Json(response);
}

int getModelFile(HttpRequest* req, HttpResponse* resp) {
    const char* filePath = PATH_MODEL_DOWNLOAD_DIR "model.cvimodel";

    if (resp->File(filePath) != 200) {
        return HTTP_STATUS_INTERNAL_SERVER_ERROR;
    }

    resp->SetHeader("Content-Type", "application/cvimodel");
    resp->SetHeader("Content-Disposition", "attachment; filename=\"model.cvimodel\"");

    return 200;
}

int uploadModel(const HttpContextPtr& ctx) {
    int ret               = 0;
    std::string modelPath = PATH_MODEL_DOWNLOAD_DIR;

    if (ctx->is(MULTIPART_FORM_DATA)) {
        ret = createFolder(PATH_MODEL_DOWNLOAD_DIR);
        if (ret == 0) {
            ret = saveModelFile(ctx, modelPath);
        }
        if (ret == 200) {
            ret = saveModelInfoFile(ctx, modelPath);
        }
    } else {
        std::string fileName = ctx->param("model_file", "model.cvimodel");
        std::string filePath = modelPath + fileName;
        ret                  = ctx->request->SaveFile(filePath.c_str());
    }

    hv::Json response;
    if (ret == 200) {
        response["code"] = 0;
        response["msg"]  = "upload model successfully";
    } else {
        response["code"] = -1;
        response["msg"]  = "upload model failed";
    }
    response["data"] = hv::Json({});

    return ctx->send(response.dump(2));
}

int getModelList(HttpRequest* req, HttpResponse* resp) {
    hv::Json response;
    uint32_t count           = 0;
    response["code"]         = 0;
    response["data"]["list"] = hv::Json::array();

    if (std::filesystem::exists(PATH_MODEL_LIST_DIR)) {
        for (auto& entry : std::filesystem::directory_iterator(PATH_MODEL_LIST_DIR)) {
            if (entry.path().extension() == ".json") {
                std::filesystem::path filePath = entry.path();
                hv::Json model;
                try {
                    hv::Json modelInfo   = hv::Json::parse(readFile(entry.path().string(), "NULL"));
                    model["id"]          = modelInfo.contains("model_id") ? modelInfo["model_id"] : "0";
                    model["name"]        = modelInfo.contains("model_name") ? modelInfo["model_name"] : "";
                    model["version"]     = modelInfo.contains("version") ? modelInfo["version"] : "";
                    model["description"] = modelInfo.contains("description") ? modelInfo["description"] : "";
                    model["md5"]         = modelInfo.contains("md5") ? modelInfo["md5"] : "";
                    model["file"]        = filePath.replace_extension(".cvimodel").string();
                    model["pic_url"]     = modelInfo.contains("pic_url") ? modelInfo["pic_url"] : "";
                    model["author"]      = modelInfo.contains("author") ? modelInfo["author"] : "";
                    model["classes"]     = modelInfo.contains("classes") ? modelInfo["classes"] : "";
                    response["data"]["list"].push_back(model);
                } catch (std::exception& e) {
                    continue;
                }
                count++;
            }
        }
    }
    response["data"]["count"] = count;

    return resp->Json(response);
}

int savePlatformInfo(HttpRequest* req, HttpResponse* resp) {
    int ret = 0;
    hv::Json response;
    std::string platformInfo = req->GetString("platform_info");

    ret = writeFile(PATH_PLATFORM_INFO_FILE, platformInfo);
    if (ret != 0) {
        response["code"] = -1;
        response["msg"]  = "Upload platform information failed!";
        response["data"] = hv::Json({});
        return resp->Json(response);
    }

    response["code"] = 0;
    response["msg"]  = "";
    response["data"] = hv::Json({});

    return resp->Json(response);
}

int getPlatformInfo(HttpRequest* req, HttpResponse* resp) {
    hv::Json response;
    std::string platformInfo = readFile(PATH_PLATFORM_INFO_FILE, "NULL");

    if (platformInfo == "NULL") {
        response["code"] = -1;
        response["msg"]  = "Platform information does not exist!";
        response["data"] = hv::Json({});
        return resp->Json(response);
    }

    response["code"]                  = 0;
    response["msg"]                   = "";
    response["data"]["platform_info"] = platformInfo;

    return resp->Json(response);
}
