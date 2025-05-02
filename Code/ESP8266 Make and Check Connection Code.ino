#include <ESP8266WiFi.h>

const char* ssid = "Airtel_Datt";     // Replace with your Wi-Fi name (SSID)
const char* password = "dattpanchal@2904"; // Replace with your Wi-Fi password

void setup() {
  Serial.begin(115200);  
  Serial.println();
  Serial.println("Connecting to Wi-Fi...");

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Connected!");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());  // Print ESP8266's assigned IP
}

void loop() {
}
