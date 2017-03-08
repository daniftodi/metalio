#ifndef METAL_METALWIFIMANAGER_H
#define METAL_METALWIFIMANAGER_H

#include <FS.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


typedef String string;

#include "holders/ArrayHolder.hpp"
#include "MetalWifiParameter.h"

class MetalWifiManager {
public:
  MetalWifiManager();
  void setWifiManager(WiFiManager*);
  void addParameter(const char*, const char*);
  WiFiManagerParameter getParameter(const string&);
  void startConfigPortal(const char*, const char*);
  void autoConnect(const char*, const char*);
  void loadData();
  void persistData();

  char mqtt_server[40];
  char mqtt_port[6];
  char mqtt_user[16];
  char mqtt_password[16];
  char mqtt_device[16];
  char mqtt_topic[63];
  char mqtt_error_topic[63];
private:
  ArrayHolder<MetalWifiParameter>* parametersHolder;

  WiFiManager* wifiManager;

  WiFiManagerParameter* custom_mqtt_server;
  WiFiManagerParameter* custom_mqtt_port;
  WiFiManagerParameter* custom_mqtt_user;
  WiFiManagerParameter* custom_mqtt_password;
  WiFiManagerParameter* custom_mqtt_device;
  WiFiManagerParameter* custom_mqtt_topic;
  WiFiManagerParameter* custom_mqtt_error_topic;
};

#endif
