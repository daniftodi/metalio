
#ifndef METAL_MQTTSTREAM_H
#define METAL_MQTTSTREAM_H

#include <Arduino.h>
#include <PubSubClient.h>
typedef String string;

class MqttStream {
public:
    MqttStream(PubSubClient* client, string topic);
    void printf(const String &);
private:
    string topic;
    PubSubClient* mqttClient;
};
#endif
