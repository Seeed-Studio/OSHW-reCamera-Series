#include <stdio.h>
#include <string>
#include <vector>
#include <syslog.h>
#include <dirent.h>

#include "hv/HttpServer.h"
#include "global_cfg.h"
#include "utils_file.h"
#include "utils_device.h"

static bool isLegalPath(const std::string& filePath) {
    std::string str[] = {
        "..",
        ".*",
        "/"
    };

    for (auto s: str) {
        if (filePath.find(s) != std::string::npos) {
            return false;
        }
    }

    return true;
}

int queryFileList(HttpRequest* req, HttpResponse* resp) {
    DIR* dir;
    struct dirent* ent;
    char fullpath[128];
    hv::Json response;
    std::vector<std::string> fileList;

    createFolder(PATH_APP_DOWNLOAD_DIR);
    dir = opendir(PATH_APP_DOWNLOAD_DIR);
    if (dir == NULL) {
        response["code"] = -1;
        response["msg"] = "open folder failed";
        response["data"] = hv::Json({});
        syslog(LOG_ERR, "open %s folder failed here\n", PATH_APP_DOWNLOAD_DIR);

        return resp->Json(response);
    }

    while((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        snprintf(fullpath, sizeof(fullpath), "%s%s", PATH_APP_DOWNLOAD_DIR, ent->d_name);
        fileList.push_back(std::string(ent->d_name));
    }
    closedir(dir);

    response["code"] = 0;
    response["msg"] = "";
    response["data"]["fileList"] = hv::Json(fileList);

    return resp->Json(response);
}

int uploadFile(HttpRequest* req, HttpResponse* resp) {
    std::string filePath = req->GetString("filePath");
    hv::Json response;
    int ret = 0;

    if (filePath.empty()) {
        filePath = req->GetParam("filePath");
    }

    if (!isLegalPath(filePath)) {
        response["code"] = -1;
        response["msg"] = "Invalid file name";
        response["data"] = hv::Json({});
        return resp->Json(response);
    }

    filePath = PATH_APP_DOWNLOAD_DIR + filePath;
    createFolder(PATH_APP_DOWNLOAD_DIR);
    ret = req->SaveFile(filePath.c_str());
    if (200 == ret) {
        response["code"] = 0;
        response["msg"] = "Upload file successfully";
    } else {
        response["code"] = -1;
        response["msg"] = "Upload file failed";
    }
    response["data"] = hv::Json({});

    return resp->Json(response);
}

int deleteFile(HttpRequest* req, HttpResponse* resp) {
    std::string filePath = req->GetString("filePath");
    hv::Json response;
    int ret = 0;

    if (filePath.empty()) {
        filePath = req->GetParam("filePath");
    }

    if (!isLegalPath(filePath)) {
        response["code"] = -1;
        response["msg"] = "Invalid file name";
        response["data"] = hv::Json({});
        return resp->Json(response);
    }

    filePath = PATH_APP_DOWNLOAD_DIR + filePath;
    ret = remove(filePath.c_str());

    if (0 == ret) {
        response["code"] = ret;
        response["msg"] = "Delete file successfully";
    } else {
        response["code"] = ret;
        response["msg"] = "Delete file failed";
    }
    response["data"] = hv::Json({});

    return resp->Json(response);
}
