
#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <PubSubClient.h>

#include "functions/PrintFunction.h"
#include "functions/CountFunction.h"
#include "metal/MqttStream.h"
#include "Metal.h"


WiFiClient wifiClient;
WiFiManager wifiManager;
PubSubClient mqttClient(wifiClient);

//MqttStream* outputStream = new MqttStream(&mqttClient, "metal/stdout");

Metal* metal = new Metal(2);
MetalWifiManager* metalWifiManager = new MetalWifiManager();

auto countFunction = new CountFunction("count");
auto sayFunction = new PrintFunction("print", &Serial);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {

  pinMode(TRIGGER_PIN, INPUT);
  Serial.begin(9600);
  Serial << "Metal init Manager";
    metalWifiManager->setWifiManager(&wifiManager);
    metalWifiManager->loadData();
    metalWifiManager->autoConnect(WIFI_SSID, WIFI_PASS);

    Serial.println("local ip");
    Serial.println(WiFi.localIP());
    Serial << "Status: " << WiFi.status() << " " << WL_CONNECTED;
    //here we have internet and can connect to mqtt broker
    mqttClient.setServer(metalWifiManager->mqtt_server, atoi(metalWifiManager->mqtt_port));
    mqttClient.setCallback(callback);

    if (mqttClient.connect(metalWifiManager->mqtt_device, metalWifiManager->mqtt_user, metalWifiManager->mqtt_password)) {
      mqttClient.publish("turnOn",metalWifiManager->mqtt_device);
      mqttClient.publish("turnOn", metalWifiManager->mqtt_topic);
      mqttClient.subscribe(metalWifiManager->mqtt_topic);
      Serial << "Subscribed to " << metalWifiManager->mqtt_topic;
  } else {
    Serial << "Something happened, can't connect to mqtt broker";
  }
}

void loop() {
  //start config portal on demand
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
      metalWifiManager->startConfigPortal(WIFI_SSID, WIFI_PASS);
  }
}
