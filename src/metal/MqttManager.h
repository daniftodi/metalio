#ifndef METAL_METAL_H
#define METAL_METAL_H
#include <Arduino.h>
typedef String string;

class MqttManager {
public:
  string getServer();
  string getPort();
  string getTopic();

  void setServer();
  void setPort();
  void setTopic();
private:
  string server;
  string port;
  string topic;
};

#endif
