#ifndef _UTILS_FILE_H_
#define _UTILS_FILE_H_

int queryFileList(HttpRequest* req, HttpResponse* resp);
int uploadFile(HttpRequest* req, HttpResponse* resp);
int deleteFile(HttpRequest* req, HttpResponse* resp);

#endif
