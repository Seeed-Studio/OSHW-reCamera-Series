#ifndef _UTILS_LED_H_
#define _UTILS_LED_H_

int ledOn(const HttpContextPtr& ctx);
int ledOff(const HttpContextPtr& ctx);
int ledBrightness(const HttpContextPtr& ctx);

#endif
