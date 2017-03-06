
#include "MqttStream.h"

MqttStream::MqttStream(PubSubClient* client, string topic) {
  this->mqttClient = client;
  this->topic = topic;
}

void MqttStream::printf(const String &message) {
  mqttClient->publish(topic.c_str(), message.c_str());
}
