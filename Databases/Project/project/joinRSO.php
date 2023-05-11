<!--------------------PHP Section----------------------------------->
<!--Checks the database for the RSO ID. If it exist, the student joins---->
<?php
require_once('connect.php');			 
session_start(); 				
if ($_SESSION['userID'] == -1) {		
    header("Location: http://localhost/Project/index");
}



$showAlert = false;
$exists=false;
$user_id = $_SESSION['userID'];
	
if($_SERVER["REQUEST_METHOD"] == "POST") {
	
	// Include file which makes the
	// Database Connection.
	require "connect.php";
	
	
	$RSO_id = $_POST["RSO_id"];
	
			
	$sql = "Select * from apart where user_id='$user_id' and RSO_id = '$RSO_id'";
	$result = mysqli_query($conn, $sql);
	$num = mysqli_num_rows($result);       
    

	
	//num==0 isn't in the apart table in the database. We can try to ins.
	if($num ==0) {
		if($exists==false){
				// insert into our database
			
			$sql = "INSERT INTO `apart` ( `user_id`,
				   `RSO_id`) VALUES ($user_id,
				$RSO_id)";
            
            
            /*if (!mysqli_query($conn,$sql)) {
                die('Error: ' . mysqli_error($conn));     // Checks if insert into the database was succesful
                } */                                      // causes a small error. Uncomment if Insert doesn't work
	
			$result = mysqli_query($conn, $sql);
			if ($result) {
				$showAlert = true;
				$sql = "Select name from rso where RSO_id='$RSO_id'";
				$welcome = mysqli_query($conn, $sql);
				$row = mysqli_fetch_array($welcome);

			}
            else {
				echo ' <div class="alert alert-danger
				alert-dismissible fade show" role="alert">
			<strong>Error!</strong>: The RSO doesnt exist'.'
			<button type="button" class="close"
				data-dismiss="alert" aria-label="Close">
				<span aria-hidden="true"></span>
			</button>
		</div>';
            }	
            
		}
		else {
		    die('Error: ' . mysqli_error($conn));
		}	
	}
	
if($num>0)
{
	$exists="You are a member of That RSO already!";
}
	
}
	
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
</head>	
<body>

<?php
	
	if($showAlert) {
	
		echo ' <div class="alert alert-success
			alert-dismissible fade show" role="alert">
			<strong>Success!</strong> You are now a member of:<strong>'.$row['name'].'</strong>
			<button type="button" class="close"
				data-dismiss="alert" aria-label="Close">
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
	
	<h1 class="text-center">Join a Registered Student Organization</h1>
	<form action="" method="post">
	
	
		<div class="form-group">
			<label for="RSO_id">RSO ID</label>
			<input type="text" class="form-control"
			id="RSO_id" name="RSO_id">
            <small id="emailHelp" class="form-text text-muted">
			All clubs have a unique RSO Id number
			</small>
		</div>
	
	
		<button type="submit" class="btn btn-primary">
		Join
		</button>

        
	</form>
	<h1 class="text-center"><?php echo($_SESSION['userName']);?> </h1>
    <h1 class="text-center"><a href="http://localhost/Project/home">Home</a> </h1>
    <h1 class="text-center"><a href="http://localhost/Project/index">Log Out</a> </h1>
    
</div>

</body>
</html>