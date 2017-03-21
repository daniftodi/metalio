# METALIO
METALIO was written in need of moving logic from microcontrollers where is hard to write code because of limited memory and processing power to more powerfull devices. With MetalIO microcontroller will know basic operations ( like put GPIO 1 to state HIGH ) and time consuming operations will happen on other devices. Functions ( aka methods ) from your microcontroller can be invoked in a secure way from anywhere in the world ( thanks to the internet and **mqtt** ). 

## Features
- Invoke remote method on your microcontroller
- Easy extend your functionality
- Move logic to more powerfull devices
- Create advanced solutions in a simple way

## How it Looks
### General overview
![MetalIO General Scheme](http://i.imgur.com/3t2XzzO.png)

### Config GUI interface

## Installing
1. Install [Platform-IO](http://platformio.org/)
2. git clone https://github.com/daniftodi/metalio.git
3. Open cloned project with Platform-IO and burn it to your device.
4. Turn on your device
5. Search for Wifi Networks ( you should find one called MetalIO ). Connect using SSID: **MetalIO**, Password: **metalio**

## Releases
#### 0.1
- Initial release 

# WifiManager
WifiManager is an open-source project that create a GUI interface for configuring ESP8266 devices, was written by [tzapu](https://github.com/tzapu/) and it's available on [https://github.com/tzapu/WiFiManager](https://github.com/tzapu/WiFiManager).

# MQTT
MQTT is a standardised publish/subscribe messaging protocol. It was designed in 1999 for use on satellites and as such is very light-weight with low bandwidth requirements making it ideal for M2M or IoT applications. As such, it has become one of the most common protocols for those situations. [Read more](https://zoetrope.io/tech-blog/brief-practical-introduction-mqtt-protocol-and-its-application-iot).

