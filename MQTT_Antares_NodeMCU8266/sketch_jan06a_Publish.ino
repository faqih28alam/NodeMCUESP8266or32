#include <AntaresESP8266MQTT.h>

#define ACCESSKEY "234a6828bfae2ca4:29d988b226be6298"
#define WIFISSID "POCO FAQ"
#define PASSWORD "kosong123"

#define projectName "Faqih"
#define deviceName "MQTTNODEMCUESP8266"

AntaresESP8266MQTT antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
}

void loop() {
  /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
   */
  antares.checkMqttConnection();

  // Variable init
  int temp = random(25,30) ;
  int hum = random(75,90);
  float windsp = float(random(20, 30))/3.33;
  float rainlv = float(random(0, 20))/6.99;
  String lat = "-6.8718189";
  String lon = "107.5872477";

  // Add variable to data storage buffer
  antares.add("temperature", temp);
  antares.add("humidity", hum);
  antares.add("wind_speed", windsp);
  antares.add("rain_level", rainlv);
  antares.add("latitude", lat);
  antares.add("longitude", lon);

  // Publish and print data
  antares.publish(projectName, deviceName);
  delay(15000);
}
