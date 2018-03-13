#include "DHTSensorFunction.h"
#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);
int DHTSensorFunction::execute(int argc, string* argv) {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    mqttClient->publish(this->deviceName, "ERROR");
    return EXIT_FAILURE;
  }

  //preparing mqtt subject
  String sensorName("/dht22");
  String deviceName(this->deviceName);
  deviceName += sensorName;

  String humidity(h, 2);
  String temperature(t, 2);
  String message("Humidity:");
  message += humidity;
  message += ";Temperature:";
  message += temperature;

  mqttClient->publish(deviceName.c_str(), message.c_str());
}
