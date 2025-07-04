#ifndef _COMMON_H_
#define _COMMON_H_

std::string getWifiConnectStatus();
bool isLegalWifiIp();

std::string getGateWay(std::string ip);
std::string getIpAddress(const char* ifrName);
std::string getNetmaskAddress(const char* ifrName);

extern uint64_t getUptime();
extern uint64_t getTimestamp();

#endif
