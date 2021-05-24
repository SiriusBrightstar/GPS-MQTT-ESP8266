#include<SoftwareSerial.h>

SoftwareSerial ss(4, 5);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  Serial.print('NEO-6m GPS Module NMEA Test:');
  Serial.println();
}

void loop() {
  while (ss.available() > 0){
    byte gpsData = ss.read();
    Serial.write(gpsData);
  }
}
