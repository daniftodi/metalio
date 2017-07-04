# METALIO
The MetalIO role is to move programming logic from microcontrollers (where memory and processing power is a problem) to more powerfull devices like Raspberry. 
With MetalIO microcontroller will know basic operations ( ex: put GPIO 1 to state HIGH ) and time consuming operations will happen on other devices. Functions from your microcontroller can be invoked in a secure way from anywhere in the world ( over internet using **mqtt protocol** ).

The MetalIO version is of the form A.B.C, where A is the major version, B is the minor version and C is the micro version. If the micro version is zero, it’s omitted from the version string, i.e. the version string is just A.B.
When a new release only fixes bugs and doesn’t add new features or functionality, the micro version is incremented. When new features are added in a backwards compatible way, the minor version is incremented and the micro version is set to zero. When there are backwards incompatible changes, the major version is incremented and others are set to zero.


## Features
- Invoke remote method from your microcontroller
- Easy extend your functionality  ( write new methods on your microcontroller )
- Move logic to more powerfull devices
- Create advanced solutions in a simple way

## How it Looks
### General overview
![MetalIO General Scheme](http://i.imgur.com/3t2XzzO.png)

### Config GUI interface

<img src='http://i.imgur.com/VYjGqcT.png' width='400px' /> <img src='http://i.imgur.com/xj0MYLg.png' width='400px' />

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

