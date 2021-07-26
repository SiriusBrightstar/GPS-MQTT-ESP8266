# GPS-MQTT-ESP8266
![Badge](https://img.shields.io/badge/Arduino-ESP8266-blue?style=for-the-badge&logo=arduino)
![Badge2](https://img.shields.io/badge/NodeJS-v14.7.3-green?style=for-the-badge&logo=node.js)

Couple of MQTT Programs I wrote for a Project. Uses ESP8266 (Tested on NodeMCU) & uBlox NEO-6m GPS Module. This repo contains:
* Program to send GPS data over MQTT.
* Program to test your GPS module.
* JavaScript Program to retrive the GPS data from MQTT Broker.

To test locally you can use Mosquitto MQTT Broker (https://mosquitto.org/).
Instructions for Linux:

```
sudo apt update
sudo apt install -y mosquitto mosquitto-clients
```

To make Mosquitto Service automatically start on Startup
```
sudo systemctl enable mosquitto.service
```
To check install version, status
```
mosquitto -v
```
If it says **"Error: Address already in use"** then it's properly installed.

To check system's IP Address and use the XXX:XXX:XXX:XXX (IPv4) address.
```
hostname -I
```
To get Latitude:
```
mosquitto_sub -t GPS/Latitude
```
To get Longitude:
```
mosquitto_sub -t GPS/Longitude
```

## Node-RED Flow

![NodeRED_Flow](https://user-images.githubusercontent.com/62252266/127009948-5af119d1-f475-49f1-a0ea-b17cbf61baaa.png)
