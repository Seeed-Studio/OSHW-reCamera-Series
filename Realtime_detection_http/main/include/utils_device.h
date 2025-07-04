#ifndef _UTILS_DEVICE_H_
#define _UTILS_DEVICE_H_

enum SERVICE_STATUS {
    SERVICE_STATUS_NORMAL      = 0,
    SERVICE_STATUS_STARTING    = 1,
    SERVICE_STATUS_STARTFAILED = 2,
    SERVICE_STATUS_ERROR       = 4,
};

extern bool g_updateStatus;

std::string readFile(const std::string& path, const std::string& defaultname = "EmptyContent");
int createFolder(const char* dirName);

void initSystemStatus();
void getSnCode();

void updateSystemThread();

int getSystemStatus(HttpRequest* req, HttpResponse* resp);
int queryServiceStatus(HttpRequest* req, HttpResponse* resp);
int getSystemUpdateVesionInfo(HttpRequest* req, HttpResponse* resp);

int queryDeviceInfo(HttpRequest* req, HttpResponse* resp);
int updateDeviceName(HttpRequest* req, HttpResponse* resp);

int updateChannel(HttpRequest* req, HttpResponse* resp);
int setPower(HttpRequest* req, HttpResponse* resp);
int updateSystem(HttpRequest* req, HttpResponse* resp);

int getUpdateProgress(HttpRequest* req, HttpResponse* resp);
int cancelUpdate(HttpRequest* req, HttpResponse* resp);

int getDeviceList(HttpRequest* req, HttpResponse* resp);
int getDeviceInfo(HttpRequest* req, HttpResponse* resp);

int getAppInfo(HttpRequest* req, HttpResponse* resp);
int uploadApp(const HttpContextPtr& ctx);

int getModelInfo(HttpRequest* req, HttpResponse* resp);
int getModelFile(HttpRequest* req, HttpResponse* resp);
int uploadModel(const HttpContextPtr& ctx);

int getModelList(HttpRequest* req, HttpResponse* resp);

int savePlatformInfo(HttpRequest* req, HttpResponse* resp);
int getPlatformInfo(HttpRequest* req, HttpResponse* resp);

#endif
