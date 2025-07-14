#include <fstream>
#include <iostream>
#include <pwd.h>
#include <stdio.h>
#include <string>
#include <syslog.h>
#include <unistd.h>
#include <vector>

#include "global_cfg.h"
#include "hv/HttpServer.h"
#include "utils_led.h"


int ledOn(const HttpContextPtr& ctx) {
    hv::Json response;

    std::string led  = ctx->param("led");
    response["code"] = 0;
    response["msg"]  = "";

    std::string path = "/sys/class/leds/" + led + "/brightness";
    if (access(path.c_str(), F_OK) != 0) {
        response["code"] = -1;
        response["msg"]  = "led not found";
        return ctx->send(response.dump(2));
    }
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        response["code"] = -1;
        response["msg"]  = "open led failed";
        return ctx->send(response.dump(2));
    }
    ofs << 1;
    ofs.close();

    return ctx->send(response.dump(2));
}

int ledOff(const HttpContextPtr& ctx) {
    hv::Json response;

    std::string led  = ctx->param("led");
    response["code"] = 0;
    response["msg"]  = "";

    std::string path = "/sys/class/leds/" + led + "/brightness";
    if (access(path.c_str(), F_OK) != 0) {
        response["code"] = -1;
        response["msg"]  = "led not found";
        return ctx->send(response.dump(2));
    }
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        response["code"] = -1;
        response["msg"]  = "open led failed";
        return ctx->send(response.dump(2));
    }
    ofs << 0;
    ofs.close();

    return ctx->send(response.dump(2));
}

int ledBrightness(const HttpContextPtr& ctx) {
    hv::Json response;

    std::string led        = ctx->param("led");
    std::string brightness = ctx->param("brightness");
    response["code"]       = 0;
    response["msg"]        = "";

    std::string path = "/sys/class/leds/" + led + "/brightness";
    if (access(path.c_str(), F_OK) != 0) {
        response["code"] = -1;
        response["msg"]  = "led not found";
        return ctx->send(response.dump(2));
    }
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        response["code"] = -1;
        response["msg"]  = "open led failed";
        return ctx->send(response.dump(2));
    }
    ofs << brightness;
    ofs.close();

    return ctx->send(response.dump(2));
}