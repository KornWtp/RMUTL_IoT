<?php  
    $conn = mysqli_connect("localhost", "iot", "1234", "iot") or die("error: ".mysqli_error($conn));
    mysqli_query($conn, "SET NAMEs 'utf8'");
    error_reporting(error_reporting & ~ENOTICE);
?>