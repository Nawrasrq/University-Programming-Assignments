<?php
// $mysqli    // = conection to database
require_once('connect.php');
session_start(); // get stored values
$_SESSION['userID'] = -1;   // -1 means user is not logged in
$_SESSION['admin_id'] = -1;


if (array_key_exists('register', $_POST)) {
    header("Location: http://localhost/Project/register");
} else if (array_key_exists('signIn', $_POST)) {
    $userName = $_POST['username'];
    $password = $_POST['password'];
    $sql = "SELECT * FROM user WHERE (user.username = '$userName' AND user.password = '$password')";
    $results = $mysqli->query($sql);
    if ($results == false) {
        echo ("Incorrect username or password");
    } else {
        while($row = $results->fetch_assoc()){
            echo($row['user_id'] );
            # values sotred across website
            $_SESSION['userID'] = $row['user_id'];
            $_SESSION['userName'] = $row['username'];
            $_SESSION['school'] = $row['school'];
            header("Location: http://localhost/Project/home");
            }
        }  
}
?>


<head>	
   <!--Using the same format as a tutorial I followed----->
	<!-- Required meta tags -->
	<meta charset="utf-8">
	<meta name="viewport" content=
		"width=device-width, initial-scale=1,
		shrink-to-fit=no">
	<!-- Bootstrap CSS -->
	<link rel="stylesheet" href=
"https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css"
		integrity=
"sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk"
		crossorigin="anonymous">
</head>	


<h1>Login</h1>
    <div class="content">
    <form method="post">
    <div class="input-field">
        <input required type="text" name="username" placeholder="Username" autocomplete="off">
      </div>
      <div class="input-field">
        <input required type="password" name="password" placeholder="Password" autocomplete="off">
      </div>

        <input type="submit" name="register" class="button" value="Register" formnovalidate/>
          
        <input type="submit" name="signIn" class="button" value="Sign In" />
    </form>
    </div>

