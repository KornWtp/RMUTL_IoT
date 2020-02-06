<?php  
    $conn = mysqli_connect("localhost", "", "", "") or die("error: ".mysqli_error($conn));
    mysqli_query($conn, "SET NAMEs 'utf8'");
    error_reporting(error_reporting & ~ENOTICE);
    date_default_timezone_set("Asia/Bankok");
?>