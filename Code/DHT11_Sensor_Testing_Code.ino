#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN D4  // Pin where DHT11 is connected
#define DHTTYPE DHT11  // Sensor type (DHT11)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
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
}
