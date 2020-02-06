<?php session_start(); ?>
<?php include("condb.php"); ?>
<?php
    $motion = $GET['motion_sensor'];
    $turbidity = $GET['turbidity_sensor'];
    $vibration = $GET['vibration_sensor'];
    $ldr = $GET['ldr_sensor'];

    $sql = "INSERT INTO iot( `motion_sensor`, `turbidity_sensor`, `vibration_sensor`, `ldr_sensor`) VALUES ($motion, $turbidity, $vibration, $ldr)";
    $sql_query($conn, $sql);
    if($sql_query) {
        echo "complete";
    } else {
        echo "error";
    }
?>
