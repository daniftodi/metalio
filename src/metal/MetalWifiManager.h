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
  MetalWifiManager(WiFiManager*, int);
  void addParameter(const char*, const char*);
  WiFiManagerParameter getParameter(const string&);
  void startConfigPortal(const char*, const char*);
  void autoConnect(const char*, const char*);
  void loadData();
  void persistData();
private:
  ArrayHolder<MetalWifiParameter>* parametersHolder;
  WiFiManager* wifiManager;

  File configFile;
  bool shouldSaveConfig = true;
};

#endif
