
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

MqttStream* outputStream = new MqttStream(&mqttClient, "metal/stdout");

Metal* metal = new Metal(2);
MetalWifiManager* metalWifiManager = new MetalWifiManager(&wifiManager, 5);

auto countFunction = new CountFunction("count");
auto sayFunction = new PrintFunction("print", &Serial);

void setup() {

  pinMode(TRIGGER_PIN, INPUT);
  Serial.begin(9600);

  Serial << "Metal put functions";
  metal->put(sayFunction);
  metal->put(countFunction);

  Serial << "Metal init Manager";
  *metal << "Metal init";
  metalWifiManager->addParameter("mqtt_server", "mqtt server");
  metalWifiManager->addParameter("mqtt_client", "mqtt client");

  metalWifiManager->autoConnect(WIFI_SSID, WIFI_PASS);
  metal->execute("print:Hello World!");

  metalWifiManager->getParameter("mqtt_server").getValue();

}

void loop() {
  //start config portal on demand
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
      metalWifiManager->startConfigPortal(WIFI_SSID, WIFI_PASS);
  }
}
