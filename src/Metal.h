//
// Created by diftodi on 2/14/17.
//

#ifndef METAL_METAL_H
#define METAL_METAL_H

#define MAX_FUNC_ARGS 10
#define MAX_ARG_LEN 16

#include <FS.h>
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

#include "abstract/Function.h"
#include "holders/ArrayHolder.hpp"
#include <Arduino.h>
typedef String string;

class Metal {
public:
    Metal(int);
    ArrayHolder<Function>* getHolder();
    string getFunctionName(const string inputQuery);
    string* getFunctionArgs(const string inputQuery);
    int execute(string inputQuery);
    void put(Function*);
    void startConfigPortal();
    void initWifiManager();
private:
    ArrayHolder<Function>* fHolder;
    WiFiManager wifiManager;

    bool shouldSaveConfig = false;

    void readConfig();
    void configSaver();
    virtual string* tokenizer(const string inputQuery, const int count);
    int getArgsCount(string* args);
};

#endif //METAL_METAL_H
