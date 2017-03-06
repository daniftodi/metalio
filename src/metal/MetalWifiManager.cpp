
#include "MetalWifiManager.h"

MetalWifiManager::MetalWifiManager(WiFiManager* wifiManager, int maxParametersCount) {
    this->parametersHolder = new ArrayHolder<MetalWifiParameter>(maxParametersCount);
    this->wifiManager = wifiManager;

    configFile = SPIFFS.open("/config.json", "r");
}

void MetalWifiManager::addParameter(const char* name, const char* title) {
  MetalWifiParameter custom_parameter(name, title, title, 63);
  wifiManager->addParameter(&custom_parameter);
  this->parametersHolder->put(&custom_parameter);
}

WiFiManagerParameter MetalWifiManager::getParameter(const string& parameterName) {
  this->parametersHolder->get(parameterName);
}

void MetalWifiManager::startConfigPortal(const char* ssid, const char* pass) {
  this->wifiManager->startConfigPortal(ssid, pass);
}

void MetalWifiManager::autoConnect(const char* ssid, const char* pass) {
  this->wifiManager->autoConnect(ssid, pass);
}

void MetalWifiManager::loadData() {

}

void MetalWifiManager::persistData() {
  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    for(int i=0; i<this->parametersHolder->size(); i++) {
      json[this->parametersHolder->get(i)->getName()] = this->parametersHolder->get(i)->getValue();
    }

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
}
