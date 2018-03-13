#ifndef METAL_DHTSENSORFUNCTION_H
#define METAL_DHTSENSORFUNCTION_H


#include "../abstract/Function.h"
#include <Arduino.h>
#include <PubSubClient.h>
typedef String string;

#ifndef PRINT_AS_STREAM
#define PRINT_AS_STREAM
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }
#endif

class DHTSensorFunction : public Function {
public:
    DHTSensorFunction() : Function() {};
    DHTSensorFunction(const string name) : Function(name){};
    DHTSensorFunction(const string name, PubSubClient *mqttClient, const char *deviceName) : Function(name){
      this->mqttClient = mqttClient;
      this->deviceName = deviceName;
    };
    int execute(int, string*);
private:
    PubSubClient *mqttClient;
    const char *deviceName;
};


#endif //METAL_DHTSENSORFUNCTION_H
