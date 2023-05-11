<?php
/*
* Change the value of $password if you have set a password on the root userid
* Change the value of $database if using diffrent database name
* Change NULL to port number to use DBMS other than the default using port 3306
*
*/
$servername = 'localhost';
$user = 'root';
$password = ''; //To be completed if you have set a password to root
$database = 'project'; //To be completed to connect to a database. The database must exist.
$port = NULL; //Default must be NULL to use default port
$mysqli = new mysqli('127.0.0.1', $user, $password, $database, $port);
$conn = mysqli_connect($servername,$user, $password, $database);//Does the same thing as $mysqli. Couldn't get $mysqli connection to work with CreateRSO.

if ($mysqli->connect_error) {
    die('Connect Error (' . $mysqli->connect_errno . ') '
            . $mysqli->connect_error);
}

if($conn->connect_error) {

    die("Error". mysqli_connect_error());
}

?>

