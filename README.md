# 🌍 IoT Based Smart Environmental Monitoring System with Linux Local Web Server

A real-time IoT system that monitors environmental temperature and humidity using DHT11 and ESP8266, logs the data to a local MySQL database hosted on a Linux server, and displays it through a dynamic PHP-based web interface.

---

## 📚 Abstract

This project aims to build an IoT-based environmental monitoring system using the ESP8266 NodeMCU and DHT11 sensor. The ESP8266 reads temperature and humidity data and transmits it via Wi-Fi to a local Linux-based server running Apache, PHP, and MySQL (XAMPP or LAMP stack). The system is scalable, low-cost, and suitable for smart home, agricultural, and industrial applications.

---

## 🎯 Objectives

- Capture real-time temperature and humidity using DHT11.
- Transmit data via Wi-Fi using the ESP8266.
- Store data locally using MySQL on a Linux server.
- Display data dynamically using a PHP/HTML-based dashboard.
- Provide a scalable and cost-effective solution for environment monitoring.

---

## 🔧 Hardware Components

| Component            | Description                                 |
|---------------------|---------------------------------------------|
| DHT11 Sensor         | Temperature and humidity sensor             |
| ESP8266 NodeMCU      | Wi-Fi microcontroller board                 |
| Resistor (10kΩ)      | Pull-up resistor for DHT11 data pin         |
| Breadboard & Wires   | For prototyping and connections             |
| Power Supply (USB)   | Powers the ESP8266                          |

---

## 💻 Software Requirements

- Arduino IDE (for programming ESP8266)
- XAMPP or LAMP Stack (Apache, MySQL, PHP)
- Web Browser (for dashboard access)
- PHP scripts (`insert_data.php`, `index.php`)
- MySQL Database (`env_monitoring`)

---

## 🧱 System Architecture

![Block Diagram](https://github.com/user-attachments/assets/070b815a-0ffa-4ad8-803d-6606fe5ae237)

## 🔌 Circuit Diagram and Connections

![Circuit Diagram](https://github.com/user-attachments/assets/de46546a-dd04-4fe7-a0b6-dc2fdc3ba4c2)

| DHT11 Pin            | NodeMCU Pin                                 |
|---------------------|---------------------------------------------|
| VCC         | 3.3V             |
| DATA      | D4 (GPIO2)                 |
| GND      | GND         |

A 10kΩ pull-up resistor is connected between DATA and VCC.

## ✅ Prerequisites

- ESP8266 NodeMCU board
- DHT11 Sensor
- Linux PC (Ubuntu preferred)
- Arduino IDE
- Internet connection

## 🔧 Steps to Build from Scratch

### Step 1: Install Apache, MySQL, PHP (LAMP Stack)

Option A: Install LAMP on Ubuntu

```
sudo apt update
sudo apt install apache2 mysql-server php libapache2-mod-php php-mysql
```

Option B: Use XAMPP (Cross-platform)
```
sudo chmod +x xampp-linux-x64-<version>.run
sudo ./xampp-linux-x64-<version>.run
sudo /opt/lampp/lampp start
```
Check if Apache is running:
```
http://localhost
```
You should see the Apache test page.

### 💾 Step 2: Create MySQL Database

Log into MySQL:
```
sudo mysql -u root -p

Create a database and table:

CREATE DATABASE env_monitoring;
USE env_monitoring;

CREATE TABLE sensor_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperature FLOAT,
    humidity FLOAT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```
Exit MySQL:
```
exit;
```

### 📂 Step 3: Create PHP Files

Navigate to your Apache server root directory:
```
cd /var/www/html
```
Create a PHP script to receive and store data

insert_data.php
```
<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "env_monitoring";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Get data from POST request
// $sensor_name = $_POST['sensor_name'];
// $value = $_POST['value'];

$sensor_name = isset($_POST['sensor_name']) ? $_POST['sensor_name'] : $_GET['sensor_name'];
$value = isset($_POST['value']) ? $_POST['value'] : $_GET['value'];


// Insert data into the table
$sql = "INSERT INTO sensor_data (sensor_name, value) VALUES ('$sensor_name', $value)";

if ($conn->query($sql) === TRUE) {
    echo "Data inserted successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
```

Create a PHP dashboard to display data

index.php
```
<?php
// Database connection
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "env_monitoring";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch data from the table
$sql = "SELECT sensor_name, value, timestamp FROM sensor_data";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="refresh" content="10">

    <title>Smart Environmental Monitoring</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f4f4f4;
	 }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
            background: #fff;
        }
        table, th, td {
            border: 1px solid #ddd;
        }
	table tr:hover {
    	    background-color: #f1f1f1;
	}

        th, td {
            padding: 10px;
            text-align: left;
        }
        th {
            background-color: #f8f8f8;
        }
    </style>
</head>
<body>
    <h1>Environmental Monitoring Data</h1>

    <?php
    if ($result->num_rows > 0) {
        echo "<table>";
        echo "<tr><th>Sensor Name</th><th>Value</th><th>Timestamp</th></tr>";
        // Output data of each row
        while($row = $result->fetch_assoc()) {
            echo "<tr><td>" . $row["sensor_name"] . "</td><td>" . $row["value"] . "</td><td>" . $row["timestamp"] . "</td></tr>";
        }
        echo "</table>";
    } else {
        echo "<p>No data available</p>";
    }
    $conn->close();
    ?>
</body>
</html>

```

### ⚙️ Step 4: Arduino Code for ESP8266

Upload this sketch using Arduino IDE:

```
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN D4  // Pin where DHT11 is connected
#define DHTTYPE DHT11  // Sensor type (DHT11)

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "";       // Your WiFi SSID
const char* password = "";   // Your WiFi Password
const char* serverIP = "";   // Run `hostname -I` on Linux terminal

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
```

## ✅ Final Notes

- Open http://localhost/index.php on your server browser to see the dashboard.
- Use Serial Monitor to debug sensor readings.
- Ensure ESP8266 and server are on the same local network.

## 📊 Output

- Data logged every 5 seconds.
- Displayed live on the local web dashboard.
- Accurate real-time insights for temperature and humidity.

## 🧪 Results
- ✅ Real-time data acquisition and logging.
- ✅ Data reliably displayed on a local network.
- ✅ System tested on multiple Wi-Fi networks with consistent performance.

## ⚠️ Limitations
- Limited sensor range (DHT11 ±2°C, ±5% RH).
- Access restricted to local network (unless port forwarding is enabled).
- Requires continuous power and Wi-Fi.

## 💡 Future Improvements
- Use more accurate sensors (e.g., DHT22, BME280).
- Integrate cloud services (Firebase, AWS).
- Enable remote notifications (SMS, email).
- Develop mobile app for easier remote access.
- Implement solar-powered operation for remote environments.

## 🏁 Applications
- 🌱 Agricultural field monitoring
- 🏠 Smart home automation
- 🏭 Industrial environment control
- 🏫 Classroom or lab air quality monitoring

## 📘 Documentation
📄 [Project Report PDF](https://github.com/DuttPanchal04/IoT-Based-Smart-Environmental-Monitoring---Linux-Web-Server/blob/main/IoT_Linux%20Environmental%20Monitoring.pdf)

💻 [PHP & Arduino Code](https://github.com/DuttPanchal04/IoT-Based-Smart-Environmental-Monitoring---Linux-Web-Server/tree/main/Code)

🖼️ [Circuit Diagram & UI](https://github.com/DuttPanchal04/IoT-Based-Smart-Environmental-Monitoring---Linux-Web-Server/blob/main/Circuit%20Diagram.png)

## 🤝 Connect
- 👨‍💻 Build by Dutt Panchal
- 📧 Email: dattpanchal2904@gmail.com
- 🔗 [Github](https://github.com/DuttPanchal04)
- 🔗 [LinkedIn](https://www.linkedin.com/in/dattpanchal04/)

⭐ If you like this project, don’t forget to give it a star and share it!
