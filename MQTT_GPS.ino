/*
	Microcontroller:	NodeMCU (ESP8266)
	Platform:		Arduino IDE
	GPS Module:		Ublox NEO-6m
	TinyGPSPlus:		https://github.com/mikalhart/TinyGPSPlus
	PubSubClient:		https://github.com/knolleary/pubsubclient
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

const char* ssid = "SSID";				//Change
const char* password = "PASSWORD";			//Change
const char* mqtt_server = "MQTT_SERVER_IP_ADDRESS";	//Change
const char* pub_LAT = "GPS/Latitude";
const char* pub_LON = "GPS/Longitude";
static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;
const unsigned int writeInterval = 5000;;

WiFiClient espClient;
PubSubClient client(espClient);
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup_wifi() {

  delay(10);
  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("¯\(°_o)/¯");
    Serial.println();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println("※\(^o^)/※");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("Connection", "Hello World");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  ss.begin(GPSBaud);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      if (gps.location.isValid()) {
        double latitude = (gps.location.lat());
        double longitude = (gps.location.lng());
        char payload_Lat[15] = "";
        char payload_Lon[15] = "";
        snprintf (payload_Lat, 15, "%lf", latitude);
        snprintf (payload_Lon, 15, "%lf", longitude);
        Serial.println("*****Publishing GPS data to MQTT Server*****");
        Serial.print("Publishing messages: \n");
        Serial.print("Latitude : ");
        Serial.println(payload_Lat);
        Serial.print("Longitude: ");
        Serial.println(payload_Lon);
        client.publish(pub_LAT, payload_Lat);
        client.publish(pub_LON, payload_Lon);
        Serial.println("GPS DATA PUBLISHED VIA MQTT");
        Serial.println("****End****");
        Serial.println();
        delay(writeInterval);// delay 
        } 
        else
          Serial.println(F("SOMETHING'S WRONG"));
    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
      while(true);
  }
}
