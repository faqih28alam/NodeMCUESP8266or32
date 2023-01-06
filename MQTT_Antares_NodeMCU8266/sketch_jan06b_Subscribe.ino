#include <AntaresESP8266MQTT.h>

#define ACCESSKEY "234a6828bfae2ca4:29d988b226be6298"
#define WIFISSID "POCO FAQ"
#define PASSWORD "kosong123"

#define projectName "Faqih"
#define deviceName "MQTTNODEMCUESP8266"

AntaresESP8266MQTT antares(ACCESSKEY);

void callback(char topic[], byte payload[], unsigned int length) {
  /*
    Get the whole received data, including the topic,
    and parse the data according to the Antares data format.
  */
  antares.get(topic, payload, length);

  Serial.println("New Message!");
  // Print topic and payload
  Serial.println("Topic: " + antares.getTopic());
  Serial.println("Payload: " + antares.getPayload());
  // Print individual data
  Serial.println("Temperature: " + String(antares.getInt("temperature")));
  Serial.println("Humidity: " + String(antares.getInt("humidity")));
  Serial.println("Wind speed: " + String(antares.getFloat("wind_speed")));
  Serial.println("Rain level: " + String(antares.getFloat("rain_level")));
  Serial.println("Latitude: " + antares.getString("latitude"));
  Serial.println("Longitude: " + antares.getString("longitude"));
}

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  antares.setCallback(callback);
}
void loop() {
  /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
  */
  antares.checkMqttConnection();
}
