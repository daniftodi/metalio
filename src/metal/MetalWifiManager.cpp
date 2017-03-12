
#include "MetalWifiManager.h"

//because of C callback ( can't cast class method as this function)
bool shouldSaveConfig = false;
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

MetalWifiManager::MetalWifiManager() {
}

void MetalWifiManager::setWifiManager(WiFiManager* wifiManager) {
      this->wifiManager = wifiManager;
}

void MetalWifiManager::addParameter(const char* name, const char* title) {
  MetalWifiParameter custom_parameter(name, title, title, 23);
  wifiManager->addParameter(&custom_parameter);
  this->parametersHolder->put(&custom_parameter);
}

WiFiManagerParameter MetalWifiManager::getParameter(const string& parameterName) {
  this->parametersHolder->get(parameterName);
}

void MetalWifiManager::startConfigPortal(const char* ssid, const char* pass) {

  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
  WiFiManagerParameter custom_mqtt_user("user", "mqtt user", mqtt_user, 16);
  WiFiManagerParameter custom_mqtt_password("password", "mqtt password", mqtt_password, 16);
  WiFiManagerParameter custom_mqtt_device("device", "device name", mqtt_device, 16);
  WiFiManagerParameter custom_mqtt_topic("topic", "mqtt topic", mqtt_topic, 63);
  WiFiManagerParameter custom_mqtt_error_topic("error_topic", "mqtt error topic", mqtt_error_topic, 63);

  this->custom_mqtt_server = &custom_mqtt_server;
  this->custom_mqtt_port = &custom_mqtt_port;
  this->custom_mqtt_user = &custom_mqtt_user;
  this->custom_mqtt_password = &custom_mqtt_password;
  this->custom_mqtt_device = &custom_mqtt_device;
  this->custom_mqtt_topic = &custom_mqtt_topic;
  this->custom_mqtt_error_topic = &custom_mqtt_error_topic;

  WiFiManager wifiManager;
  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_device);
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_password);
  wifiManager.addParameter(&custom_mqtt_topic);
  wifiManager.addParameter(&custom_mqtt_error_topic);

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  wifiManager.startConfigPortal(ssid, pass);

  this->persistData();
}

void MetalWifiManager::autoConnect(const char* ssid, const char* pass) {
  //load persisted data before trying to connect
  this->loadData();
  this->wifiManager->autoConnect(ssid, pass);
}

void MetalWifiManager::loadData() {
  Serial.println("Begin Load data method");
  if (SPIFFS.begin()) {
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
          strcpy(mqtt_user, json["mqtt_user"]);
          strcpy(mqtt_password, json["mqtt_password"]);
          strcpy(mqtt_device, json["mqtt_device"]);
          strcpy(mqtt_topic, json["mqtt_topic"]);
          strcpy(mqtt_error_topic, json["mqtt_error_topic"]);

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
}
}

void MetalWifiManager::persistData() {
  //save the custom parameters to FS
  if (shouldSaveConfig) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    //read upaded parameters
    strcpy(mqtt_server, custom_mqtt_server->getValue());
    strcpy(mqtt_port, custom_mqtt_port->getValue());
    strcpy(mqtt_user, custom_mqtt_user->getValue());
    strcpy(mqtt_password, custom_mqtt_password->getValue());
    strcpy(mqtt_device, custom_mqtt_device->getValue());
    strcpy(mqtt_topic, custom_mqtt_topic->getValue());
    strcpy(mqtt_error_topic, custom_mqtt_error_topic->getValue());

    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["mqtt_user"] = mqtt_user;
    json["mqtt_password"] = mqtt_password;
    json["mqtt_device"] = mqtt_device;
    json["mqtt_topic"] = mqtt_topic;
    json["mqtt_error_topic"] = mqtt_error_topic;

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
