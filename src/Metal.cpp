//
// Created by diftodi on 2/14/17.
//

#include "Metal.h"

void saveConfigCallback () {
  Serial.println("Should save config");
}

Metal::Metal(int maxFunctionHolder) {
    this->fHolder = new ArrayHolder<Function>(maxFunctionHolder);
}

ArrayHolder<Function>* Metal::getHolder() {
    return this->fHolder;
}

string Metal::getFunctionName(const string inputQuery) {
    return *this->tokenizer(inputQuery,1);
}

string* Metal::getFunctionArgs(const string inputQuery) {
    return this->tokenizer(inputQuery, -1);
}

string* Metal::tokenizer(const string inputQuery, const int count) {
    char *token;
    string *args = new string[MAX_FUNC_ARGS];
    int counter = 0, downCounter = count;
    char* copy = strdup(inputQuery.c_str());
    token = strtok(copy, ":");
    while(token != NULL) {
        args[counter] = new char[MAX_ARG_LEN];
        args[counter++] = token;
        token = strtok(NULL, ",");
        if(0 == --downCounter) break;
    }
    args[counter] = "";
    free(copy);
    return args;
}

void Metal::put(Function* function) {
    this->fHolder->put(function);
}

int Metal::getArgsCount(string* args) {
    int count = 0;
    while(args[count++] != "");

    return count-1;
}

int Metal::execute(string inputQuery) {
    string *argsContainer = this->getFunctionArgs(inputQuery);
    string functionName = this->getFunctionName(inputQuery);
    Function* currentFunction = this->getHolder()->get(functionName);
    if(currentFunction != NULL) {
        currentFunction->execute(this->getArgsCount(argsContainer), argsContainer);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

void Metal::readConfig() {
    /*if (SPIFFS.begin()) {
      Serial.println("mounted file system");
      if (SPIFFS.exists("/config.json")) {
        //file exists, reading and loading
        Serial.println("reading config file");
        File configFile = SPIFFS.open("/config.json", "r");
        if (configFile) {
          Serial.println("opened config file");
          size_t size = configFile.size();
          // Allocate a buffer to store contents of the file.
          std::unique_ptr<char[]> buf(new char[size]);

          configFile.readBytes(buf.get(), size);
          DynamicJsonBuffer jsonBuffer;
          JsonObject& json = jsonBuffer.parseObject(buf.get());
          json.printTo(Serial);
          if (json.success()) {
            Serial.println("\nparsed json");

            strcpy(mqtt_server, json["mqtt_server"]);
            strcpy(mqtt_port, json["mqtt_port"]);
            strcpy(mqtt_topic, json["mqtt_topic"]);

          } else {
            Serial.println("failed to load json config");
          }
        }
      }
    } else {
      Serial.println("failed to mount FS");
  } */
}

void Metal::initWifiManager() {
    //this->readConfig();


    char mqtt_server[40] = "mqtt server";
    char mqtt_port[6] = "8080";
    char mqtt_topic[63] = "mqtt/topic";

    WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
    WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
    WiFiManagerParameter custom_mqtt_topic("topic", "mqtt topic", mqtt_topic, 63);

    wifiManager.addParameter(&custom_mqtt_server);
    wifiManager.addParameter(&custom_mqtt_port);
    wifiManager.addParameter(&custom_mqtt_topic);
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    if(!this->wifiManager.autoConnect(WIFI_SSID, WIFI_PASS)){
      ESP.reset();
      delay(5000);
    }

    //after succesful connection
    /*strcpy(this->mqtt_server, custom_mqtt_server.getValue());
    strcpy(this->mqtt_port, custom_mqtt_port.getValue());
    strcpy(this->mqtt_topic, custom_mqtt_topic.getValue());

    if (this->shouldSaveConfig) {
        Serial.println("saving config");
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.createObject();
        json["mqtt_server"] = mqtt_server;
        json["mqtt_port"] = mqtt_port;
        json["mqtt_topic"] = mqtt_topic;

        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile) {
          Serial.println("failed to open config file for writing");
        }

        json.printTo(Serial);
        json.printTo(configFile);
        configFile.close();
        //end save
    } */

}

void Metal::configSaver() {
   this->shouldSaveConfig = true;
}

void Metal::startConfigPortal() {
    this->wifiManager.startConfigPortal(WIFI_SSID, WIFI_PASS);
}
