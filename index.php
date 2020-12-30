<?php header( "refresh:1" );
$dbname = 'id15612948_ismis';
$dbuser = 'id15612948_soy';  
$dbpass = '_Soygwapokaayo345'; 
$dbhost = 'localhost'; 

$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}

// echo "Connection Success!<br><br>";

$temperature = $_GET["temperature"];
$water_level = $_GET["water_level"];


$query = "UPDATE temperature SET temperature = ('$temperature'),water_level = ('$water_level')";
mysqli_query($connect,$query);

// echo "Insertion Success!<br>";

?>

<html>

<header>
<title> Hydrophonic System DS18B20 </title>

<style>
html *
{
   font-family: Arial !important;
   font-size: 5rem;
}
</style

</header>

<body>
    <h1>Hydrophonics System (DS18B20 and Float Switch) v1.0</h1>

    <?php
    $query2 = "SELECT temperature from temperature";
    $row = mysqli_query($connect,$query2);
    
    while($data = $row->fetch_assoc()){
        if($data["temperature"] > 40){
           echo "<h2 style='color:red'>Temperature: ". $data["temperature"]." Celsius</h2>"; 
        }else if($data["temperature"] <= 40 && $data["temperature"] > 25){
           echo "<h2 style='color:green'>Temperature: ". $data["temperature"]." Celsius</h2>";  
        }else{
            echo "<h2 style='color:blue'>Temperature: ". $data["temperature"]." Celsius</h2>"; 
        }
    }
    $query3 = "SELECT water_level from temperature";
    $rows = mysqli_query($connect,$query3);
    
    while($state = $rows->fetch_assoc()){
        
        if( strcmp($state['water_level'],"HIGH")  == 0){
            echo "<h2 style='color:red'>Water Level: ".$state['water_level'];
        }else if( strcmp($state['water_level'],"LOW")  == 0 ){
            echo "<h2 style='color:green'>Water Level: ".$state['water_level'];
        }
        echo "</h2>";
    }
?> 
</body>
</html>