<?php
require_once('connect.php');			 
session_start(); 				
if ($_SESSION['userID'] == -1) {		
    header("Location: http://localhost/Project/index");
}


$showAlert = false;
$exists=false;


if($_SERVER["REQUEST_METHOD"] == "POST") {
	
	// Include file which makes the
	// Database Connection.
	require "connect.php";
	
	
  $address = $_POST["address"];
  $name = $_POST["name"];
  $long = $_POST["long"];
  $lat = $_POST["lat"];
  $_SESSION['address']= $address;
  
	
			
	$sql = "Select * from location where address='$address'";
	$result = mysqli_query($conn, $sql);
	$num = mysqli_num_rows($result); 
        

	//num==0 isn't in the apart table in the database. We can try to ins.
	if($num ==0) {
		if($exists==false){
				// insert into our database
			
			$sql = "INSERT INTO `location` ( `address`,`longitude`,`latitude`) VALUES (
				'$address',$long,$lat)";
            
            
            /*if (!mysqli_query($conn,$sql)) {
                die('Error: ' . mysqli_error($conn));     // Checks if insert into the database was succesful
                } */                                      // causes a small error. Uncomment if Insert doesn't work
	
			$result = mysqli_query($conn, $sql);
			if ($result) {
				$showAlert = true;
			}
            /*else {
                die('Error: ' . mysqli_error($conn)); //something went wrong
            }	*/
            
		}
		else {
		    die('Error: ' . mysqli_error($conn));
		}	
	}
	
if($num>0)
{
	$exists="This event has been created at the Given Address already";
}
	
}
	
?>





<!--------------------------End of PHP---------------------------------->






<!DOCTYPE html>
<html>
  <head>
    <h1 class="text-center">Choose a Location</h1>
    <script src="https://polyfill.io/v3/polyfill.min.js?features=default"></script>
    <link rel="stylesheet" type="text/css" href="style.css" />
    <script src="google.js"></script>
    	
   <!--Used the same format as a tutorial I followed----->
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
  <body>

  <?php
	
	if($showAlert) {
	
		echo ' <div class="alert alert-success
			alert-dismissible fade show" role="alert">
			<strong>Success!</strong> 
			<button type="button" class="close"
				data-dismiss="alert" aria-label="Close">
				<span aria-hidden="true"></span>
			</button>
		</div> ';
		header("Location: http://localhost/Project/createEvent");
		
	}
	
		
	if($exists) {
		echo ' <div class="alert alert-danger
			alert-dismissible fade show" role="alert">
		<strong>Error!</strong> '. $exists.'
		<button type="button" class="close"
			data-dismiss="alert" aria-label="Close">
			<span aria-hidden="true"></span>
		</button>
	</div>';
	}
?>
	
   
  <div id="map"></div>
    <!-- Async script executes immediately and must be after any DOM elements used in callback. -->
    <script
      src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBjhKZhOJ1ulsMnasIc1xf6_nkqiYx8cxo&callback=initMap&v=weekly"
      async
    ></script>
    
    <div class="form-group">
    <form action="" method="post"> 

    <label for="long">Longitute:</label>
      <input type="text" id="long" name ="long">

      <label for="lat">Latitude:</label>
      <input type="text" id="lat" name ="lat">

      <label for="address">Address:</label>
      <input type="text" id="address" name="address">
		
      <br>
      <button type="submit" class="btn btn-primary">
		Confirm
		</button>
  
	</form>
		</div>
   <h1 class="text-center"><?php echo($_SESSION['userName']);?> </h1>
    <h1 class="text-center"><a href="http://localhost/Project/home">Home</a> </h1>
    <h1 class="text-center"><a href="http://localhost/Project/index">Log Out</a></h1>
  



  </body>
  
</html>