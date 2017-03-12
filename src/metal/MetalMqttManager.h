#ifndef METAL_METALMQTTMANAGER_H
#define METAL_METALMQTTMANAGER_H

#include "MetalWifiManager.h";
#include <PubSubClient.h>

#include <Arduino.h>
typedef String string;

#ifndef PRINT_AS_STREAM
#define PRINT_AS_STREAM
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }
#endif
class MetalMqttManager {
public:
   MetalMqttManager();
   MetalMqttManager(MetalWifiManager*, PubSubClient*, MQTT_CALLBACK_SIGNATURE);
   void setWifiManager(MetalWifiManager*);
   void setPubSubClient(PubSubClient*);
   void setCallback(MQTT_CALLBACK_SIGNATURE);
   void setOutputStream(Stream*);
   void loop();
private:
  void mqttConnect();

  Stream* stream;
  MetalWifiManager* metalWifiManager;
  PubSubClient* mqttClient;
};
#endif
