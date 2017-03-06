

#ifndef METAL_METALWIFIPARAMETER_H
#define METAL_METALWIFIPARAMETER_H
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

class MetalWifiParameter : public Item, public WiFiManagerParameter  {
public:
    MetalWifiParameter(const char *custom) : WiFiManagerParameter(custom) {};

    MetalWifiParameter(const char *id, const char *placeholder, const char *defaultValue, int length) :
      WiFiManagerParameter(id, placeholder, defaultValue, length) {};

    MetalWifiParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom) :
      WiFiManagerParameter(id, placeholder, defaultValue, length, custom) {};

    void setParamValue(const char* value) {
      strcpy(this->value, value);
    }
    char* getParamValue() {
      strcpy(this->value,this->getValue());
      return value;
    }
protected:
  char value[63];
};

#endif
