<?php session_start(); ?>
<?php include("condb.php"); ?>
<?php
    $turbidity= $_GET['turbidity'];
    $vibration = $_GET['vibration'];
    $ldr = $_GET['ldr_sensor'];
    $voltage = $_GET['voltage'];

    $sql = "INSERT INTO iot( `turbidity`, `vibration`, `ldr_sensor`, `voltage`) VALUES ('$turbidity', '$vibration', '$ldr, '$voltage')";
    $sql_query($conn, $sql);
    
    if($sql_query) {
        echo "complete";
    } else {
        echo "error";
    }
?>
