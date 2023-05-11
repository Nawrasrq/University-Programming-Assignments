<?php
// $mysqli    // = conection to database
require_once('connect.php');

if (array_key_exists('login', $_POST)) {
    header("Location: http://localhost/Project/index");
} else if (array_key_exists('signUp', $_POST)) {
    if ($_POST['password'] == $_POST['password2']) {
        $userName = $_POST['username'];
        $password = $_POST['password'];
        $email = $_POST['email'];
        $boom = explode('@', $email);
        $school = array_pop($boom);
        // Insert query
        $sql = "INSERT INTO `user` (`user_id`, `email`, `school`, `username`, `password`) VALUES (NULL, '$email', '$school', '$userName', '$password') ";
        $results = $mysqli->query($sql);
        if ($results == false) {
            echo ("Email or UserName already in use.");
        } else {
            echo ("User registered succesfully.");
            }
    } else {
        echo("Paswords don't match!");
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

<h1>Register</h1>
    <div class="content">
    <form method="post">
        <div class="input-field">
            <input required type="text" name="username" placeholder="Username" autocomplete="off">
        </div>
        <div class="input-field">
            <input required type="password" name="password" placeholder="Password" autocomplete="off">
        </div>
        <div class="input-field">
            <input required type="password" name="password2" placeholder="Re-Password" autocomplete="off">
        </div>

        <div class="input-field">
            <input required type="email" name="email" placeholder="School Email" autocomplete="off">
        </div>

        <input type="submit" name="login" class="button" value="Login" formnovalidate/>
          
        <input type="submit" name="signUp" class="button" value="Sign Up" />
    </form>
    </div>
<?php

//<input type="email" name="username" placeholder="Username" autocomplete="nope">
//echo("test")
?>
