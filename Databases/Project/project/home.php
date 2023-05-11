<?php
// start of Code required to be logged in
require('connect.php');
session_start(); // get stored values
if ($_SESSION['userID'] == -1) {
    header("Location: http://localhost/Project/index");
}


$user_id = $_SESSION["userID"];




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

<div>
<h1 class = "text-center">Welcome</h1>
<form method="post">
     
       <h2 style="margin-bottom: 10px;" ><a href="createRSO.php"><strong>Create RSO</strong></a></h2>
	   <h2><a href="joinRSO.php"><strong>Join RSO</strong></a> </h2>
	   <h2><a href="viewRSO.php"><strong>View RSO</strong></a> </h2>
	   <h2><a href="map.php"><strong>Create an Event </strong></a></h2>
	   <h2><a href="viewEvents.php"><strong>View Events</strong></a></h2>

     
	<h1 class="text-center"><?php echo($_SESSION['userName']);?> </h1>
    <h1 class = "text-center"><a href="http://localhost/Project/index">Log Out</a> </h1>
	</form>
</div>


<?php   // hiddent super admin buttons

$school = $_SESSION['school'];
$sql = "SELECT uni_pro.uni_id FROM uni_pro WHERE uni_pro.school = '$school'";
$result = $mysqli->query($sql);
#$uniId = $results->fetch_assoc()
if (mysqli_num_rows($result) == 0) {  // university profile dose not exist 
	// create profile
	$_SESSION['adminId'] = -1;
	?>
	<h2><a href="createUprofile.php"><strong>Create University profile</strong></a></h2>
	<?php

} else {
	$userId = $_SESSION['userID'];
	$row = $result->fetch_assoc();
	$uniId = $row['uni_id'];
	$sql = "SELECT superadmin.uni_id FROM superadmin WHERE (superadmin.user_id = '$userId' AND superadmin.uni_id = '$uniId')";
	$result = $mysqli->query($sql);
	if (mysqli_num_rows($result) == 0) { // university profile exists and user is not a super admin
		$_SESSION['adminId'] = $row['uni_id'];
	} else { // user is super admin
		$row = $result->fetch_assoc();
		$_SESSION['adminId'] = $row['uni_id'];
		?>
		<h2><a href="viewEventRequests.php"><strong>Approve Evnets</strong></a></h2>
		<?php
		// display super admin button
	}
}

?>