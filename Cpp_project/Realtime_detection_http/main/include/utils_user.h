#ifndef _UTILS_USER_H_
#define _UTILS_USER_H_

#include <iomanip>
#include <random>
#include <unordered_map>

extern int g_userId;

int initUserInfo();

int queryUserInfo(HttpRequest* req, HttpResponse* resp);
int updateUserName(HttpRequest* req, HttpResponse* resp);
int updatePassword(HttpRequest* req, HttpResponse* resp);
int addSShkey(HttpRequest* req, HttpResponse* resp);
int deleteSShkey(HttpRequest* req, HttpResponse* resp);
int login(HttpRequest* req, HttpResponse* resp);
int authorization(HttpRequest* req, HttpResponse* resp);
int setSShStatus(HttpRequest* req, HttpResponse* resp);

#endif
