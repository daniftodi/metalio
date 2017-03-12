
#include "MetalMqttManager.h"

MetalMqttManager::MetalMqttManager() {

}

MetalMqttManager::MetalMqttManager(MetalWifiManager* metalWifiManager, PubSubClient* pubSubClient, MQTT_CALLBACK_SIGNATURE) {
  this->setWifiManager(metalWifiManager);
  this->setPubSubClient(pubSubClient);
  this->setCallback(callback);
}

void MetalMqttManager::setOutputStream(Stream *stream) {
  this->stream = stream;
}

void MetalMqttManager::setWifiManager(MetalWifiManager *metalWifiManager) {
  this->metalWifiManager = metalWifiManager;
}

void MetalMqttManager::setPubSubClient(PubSubClient *pubSubClient) {
  this->mqttClient = pubSubClient;
}

void MetalMqttManager::setCallback(MQTT_CALLBACK_SIGNATURE) {
      mqttClient->setCallback(callback);
}

void MetalMqttManager::mqttConnect() {
    mqttClient->setServer(metalWifiManager->mqtt_server, atoi(metalWifiManager->mqtt_port));

    if (mqttClient->connect(metalWifiManager->mqtt_device, metalWifiManager->mqtt_user, metalWifiManager->mqtt_password)) {
      mqttClient->publish("deviceOn", metalWifiManager->mqtt_device);
      mqttClient->publish("listeningTopic", metalWifiManager->mqtt_topic);
      mqttClient->subscribe(metalWifiManager->mqtt_topic); //
      (*stream) << "Subscribed to " << metalWifiManager->mqtt_topic << "\n";
    } else {
      (*stream) << "Something happened, can't connect to mqtt broker";
    }
}

void MetalMqttManager::loop() {
  if (!mqttClient->connected()) {
    mqttConnect();
  }
  mqttClient->loop();
}
