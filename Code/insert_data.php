
<?php
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

