<!--------------------PHP Section----------------------------------->
<!--Sends input to the Database to confirm user has a valid admin ID. Also confirms name isn't already used for RSO---->
<?php

require_once('connect.php');			 
session_start(); 				
if ($_SESSION['userID'] == -1) {		
    header("Location: http://localhost/Project/index");
}

$admin_id = $_SESSION["admin_id"]; // get the current users admin ID so the event can be created with it
$showAlert = false;
$showError = false;
$exists=false;
$location = $_SESSION['address'];
$school=$_SESSION['school'];

if($_SERVER["REQUEST_METHOD"] == "POST") {
	// Include file which makes the
	// Database Connection.
	require "connect.php";
    

    // This is what is getting inputted from the website. We dont need $admin_id since its already stored in the session array.
	$name = $_POST["name"];
    $category = $_POST["category"];
    $description = $_POST["description"];
    $email = $_POST["email"];
    $phone = $_POST["phone"];
	$timestamp = $_POST["timestamp"];
	
	$sql = "Select * from event where name= '$name'";
	$result = mysqli_query($conn, $sql);
	$num = mysqli_num_rows($result); // Check if name is in database already.
	
	//num==0 the RSO name isn't in our database.
	if($num == 0) {
		if($exists==false){
	
		
				// insert into our database
			
			$sql = "INSERT INTO `event` ( `name`,`category`,
            `description`,`email`,`phone`,`location`,`date_time`,`school`) VALUES ('$name','$category','$description',
                '$email','$phone','$location','$timestamp','$school')";
            
            
            /*if (!mysqli_query($conn,$sql)) {
                die('Error: ' . mysqli_error($conn));     // Checks if insert into the database was succesful
                }  */                                 // causes a small error. Uncomment if Insert doesn't work
	
			$result = mysqli_query($conn, $sql);
			if ($result) {
				$showAlert = true;
			}
		}
		else {
			$showError = "Something went wrong";
		}	
	}
	
if($num>0)
{
	$exists="You created an event with this name already";
}
	
}// endif
	
?>
	
<!--------------------------------------Front end for the RSO--------------------------------------->
<!doctype html>	
<html lang="en">
<head>	
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
		<script src="google.js"></script>
</head>	
<body>

<?php
	
	if($showAlert) {
	
		echo ' <div class="alert alert-success
			alert-dismissible fade show" role="alert">
			<strong>Success!</strong> Event Created!
			<button type="button" class="close"
				data-dismiss="alert" aria-label="Close">
				<span aria-hidden="true"></span>
			</button>
		</div> ';
	}
	
	if($showError) {
	
		echo ' <div class="alert alert-danger
			alert-dismissible fade show" role="alert">
		<strong>Error!</strong> '. $showError.'
	<button type="button" class="close"
			data-dismiss="alert aria-label="Close">
			<span aria-hidden="true"></span>
	</button>
	</div> ';
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

<div class="container my-4 ">
	
	<h1 class="text-center">Event Details</h1>
	<form action="" method="post">
	
		<div class="form-group">
			<label for="name">Name of event</label>
		<input type="text" class="form-control" id="name"
			name="name" aria-describedby="emailHelp">	
		</div>
		
	
		    <div class="form-group">
  			<label for="category" >Category:</label>
        <select name="category" id="category">
        <option value="Public">public</option>
        <option value="Private">private</option>
        <option value="RSO">RSO</option>                               
    	</select>

		</div>
	
		<div class="form-group">
			<label for="description">About the event</label>
			<input type="text" class="form-control"
				id="description" name="description">
	        
			<small id="emailHelp" class="form-text text-muted">
		    Brief introduction about your event
			</small>
		</div>

        
		<div class="form-group">
			<label for="email">Event email</label>
			<input type="text" class="form-control"
				id="email" name="email">
	        
			<small id="emailHelp" class="form-text text-muted">
		    Where can you be contacted about this event?
			</small>
		</div>

        
		<div class="form-group">
			<label for="phone">Phone Number</label>
			<input type="tel" class="form-control"
				id="phone" name="phone">
	        
			<small id="emailHelp" class="form-text text-muted">
		    Best number to contact Organizer
			</small>
		</div>
		
		<div class="form-group">
			<label for="timestamp">Date</label>
			<input type="datetime-local" class="form-control"
				id="timestamp" name="timestamp">
	        
			<small id="emailHelp" class="form-text text-muted">
		    What time and day
			</small>
		</div>
         
		<button type="submit" class="btn btn-primary">
		Create Event
		</button>

        
	</form>
	<h1 class="text-center"><?php echo($_SESSION['userName']);?> </h1>
	<h1 class="text-center"><a href="http://localhost/Project/home">Home</a> </h1>
    <h1 class="text-center"><a href="http://localhost/Project/index">Log Out</a> </h1>

</div>
</body>
</html>



