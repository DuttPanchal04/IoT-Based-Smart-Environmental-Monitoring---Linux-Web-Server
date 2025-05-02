#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN D4  // Pin where DHT11 is connected
#define DHTTYPE DHT11  // Sensor type (DHT11)

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Datt Panchal";       // Your WiFi SSID
const char* password = "datt2904";   // Your WiFi Password
const char* serverIP = "192.168.43.138";   // Run `hostname -I` on Linux terminal

WiFiClient client;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
    Serial.print("ESP8266 IP Address: ");
    Serial.println(WiFi.localIP());

    dht.begin();
}

void loop() {

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String serverPath = "http://" + String(serverIP) + "/insert_data.php";
        
        float temperature = dht.readTemperature();  // Read temperature in Celsius
        float humidity = dht.readHumidity();  // Read humidity

        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
        } else {
            Serial.print("Temperature: ");
            Serial.print(temperature);
            Serial.print("°C  Humidity: ");
            Serial.print(humidity);
            Serial.println("%");
        }

        delay(2000);  // Wait 2 seconds before next reading


        String sensor_name = "Temperature ( C )";
        //float value = 25.6;  // Example value

        String postData = "sensor_name=" + sensor_name + "&value=" + String(temperature);

        Serial.println("Sending Data to Server...");
        http.begin(client, serverPath);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        int httpResponseCode = http.POST(postData);
        
        Serial.print("HTTP Response Code: ");
        Serial.println(httpResponseCode);

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Server Response: " + response);
        } else {
            Serial.println("Error Sending Data!");
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected!");
    }

    delay(5000);  // Send data every 5 seconds
}