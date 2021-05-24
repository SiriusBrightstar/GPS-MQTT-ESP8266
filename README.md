# MQTT-Stuff
Couple of MQTT Codes I wrote for a Project

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
mosquitto_sub -d -t GPS/Latitude
```
To get Longitude:
```
mosquitto_sub -d -t GPS/Longitude
```
