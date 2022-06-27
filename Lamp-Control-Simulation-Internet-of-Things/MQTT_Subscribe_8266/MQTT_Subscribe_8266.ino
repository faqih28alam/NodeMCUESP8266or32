#include <AntaresESP8266MQTT.h>     // Inisiasi library MQTT Antares

#define ACCESSKEY "f7e014c81dd014ee:e8a270226e1134a5"       // Ganti dengan access key akun Antares anda
#define WIFISSID "kuntul"         // Ganti dengan SSID WiFi anda
#define PASSWORD "syalalala"     // Ganti dengan password WiFi anda

#define applicationName "Uhuy"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Ultrasonik"     // Ganti dengan device Antares yang telah dibuat

const int relay1 = 14;

AntaresESP8266MQTT antares(ACCESSKEY);    // Buat objek antares

/*
  Fungsi utama untuk mendapatkan topik dan payload dari setiap
  pesan MQTT yang diterima oleh ESP8266.
*/
void callback(char topic[], byte payload[], unsigned int length) {

  antares.get(topic, payload, length);  // Menyimpan topic dan payload ke penampungan data sementara

  Serial.println("New Message!");
  Serial.println("Topic: " + antares.getTopic());     // Print topic
  Serial.println("Payload: " + antares.getPayload()); // Print payload

  // Print data-data yang telah didapatkan
  Serial.println("Status Lampu: " + antares.getString("Status Lampu"));  
}

void setup() {
  Serial.begin(115200);     // Buka komunikasi serial dengan baudrate 115200
  pinMode(relay1, OUTPUT);
  
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  antares.setMqttServer();  // Inisiasi server MQTT Antares
  antares.setCallback(callback);  // Set fungsi callback menjadi fungsi callback seperti di atas
}
void loop() {
  /*
    Cek koneksi ke broker MQTT Antares. Jika disconnect,
    akan dicoba untuk menyambungkan lagi
   */
  antares.checkMqttConnection();
  String stat1 = antares.getString("Status Lampu");
          delay(1000);
        if(stat1=="Nyala"){
          digitalWrite(relay1, LOW);
          Serial.println("Nyala");
          delay(1000);
        }
        if(stat1=="Mati"){
          digitalWrite(relay1, HIGH);
          Serial.println("Mati");
          delay(1000);
        }
}
