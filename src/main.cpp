
#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <PubSubClient.h>

#include "functions/PrintFunction.h"
#include "functions/CountFunction.h"
#include "functions/DigitalWriteFunction.h"
#include "functions/DHTSensorFunction.h"
#include "metal/MetalMqttManager.h";
#include "Metal.h"

//mqtt callback used to receive messages
void mqttReceiver(char* topic, byte* payload, unsigned int length);

//data initialization
WiFiClient wifiClient;
WiFiManager wifiManager;
PubSubClient mqttClient(wifiClient);

Metal* metal = new Metal(4);
MetalWifiManager* metalWifiManager = new MetalWifiManager();
MetalMqttManager* metalMqttManager;

//metal supported functions initialization
auto countFunction = new CountFunction("count");
auto printFunction = new PrintFunction("print", &Serial);
auto digitalWriteFunction = new DigitalWriteFunction("digitalWrite");
auto dhtSensorFunction = new DHTSensorFunction("dht22", &mqttClient, metalWifiManager->mqtt_device);

void setup() {
  pinMode(TRIGGER_PIN, INPUT);
  Serial.begin(9600);

  //adding MetalIO supported functions
  metal->put(countFunction);
  metal->put(printFunction);
  metal->put(digitalWriteFunction);
  metal->put(dhtSensorFunction);

  //initializing & connecting to Wifi newtork
  metalWifiManager->setWifiManager(&wifiManager);
  metalWifiManager->autoConnect(WIFI_SSID, WIFI_PASS);

  //setup mqtt connection
  metalMqttManager = new MetalMqttManager(metalWifiManager, &mqttClient, mqttReceiver);
  metalMqttManager->setOutputStream(&Serial);
}

void loop() {
  //start config portal on demand
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
      metalWifiManager->startConfigPortal(WIFI_SSID, WIFI_PASS);
  }
  metalMqttManager->loop();
}

//mqtt callback implementation
void mqttReceiver(char* topic, byte* payload, unsigned int length) {
 Serial << "Message arrived [" << topic << "]" << "\n";
 string query = (const char*) payload;
 query = query.substring(0,length);

 if(metal->execute(query) == EXIT_FAILURE) {
   mqttClient.publish(metalWifiManager->mqtt_error_topic, "Failed to execute last command");
 }
}
