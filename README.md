# mqtt-temperature-sensor
A simple project to write data from a temperature sensor to an MQTT broker.  This can either be a broker on the local network, such as [Mosquitto](https://mosquitto.org/) or the cloud based broker of your choice.

## Components

The following components are used for this project:

* Arduino UNO
* Arduino Ethernet Shield
* DHT22 temperature and humidity sensor

The layout is fairly simple.  With the enternet shield mounted on the Arduino UNO, connect the VDD pin directly to 5V, the GND to GND and the DATA pin to pin 3 of the Arduino board as follows:

![breadboard layout](https://cdn.rawgit.com/neilharvey/iot-temperature-sensor/master/breadboard.svg)

## Uploading to an Arduino Board

Before uploading the code to your board, you will need to set the address of your MQTT broker.
Either by specifying the domain name:
```Arduino
char server[] = "your.mqttserver.com";
```
Or by using an IP address (e.g. if using a local network broker):
```Arduino
IPAddress server(192, 168, 1, 100);
```

You can also change the mac address and fixed local IP address if required: 
```Arduino
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);
```
Changing the mac address is only needed when you have multiple Arduinos connected to your
local network at the same time.  The local IP address is only used when DHCP is not available on your network, 
or fails to assign an IP address.
