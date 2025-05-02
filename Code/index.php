<?php
// Database connection
$servername = "localhost";
$username = "root";
$password = "D@ttpanchal2904";
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

