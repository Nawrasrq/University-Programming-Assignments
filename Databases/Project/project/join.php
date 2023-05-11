<?php
require_once('connect.php');			 
session_start(); 				
if ($_SESSION['userID'] == -1) {		
    header("Location: http://localhost/Project/index");
}




$user_id = $_SESSION['userID'];

  // Include file which makes the
	// Database Connection.
	require "connect.php";
	
	//$sql = "Select * from apart where user_id='$user_id' and RSO_id = Select * from ";

  $sql = "Select * from rso where rso.RSO_id NOT IN (Select apart.RSO_id from apart where apart.user_id = '$user_id')";
	$result = mysqli_query($conn, $sql);
	$num = mysqli_num_rows($result); 

  $sql2 = "Select * from rso where rso.RSO_id IN (Select apart.RSO_id from apart where apart.user_id = '$user_id')";
	$result2 = mysqli_query($conn, $sql2);
	$num2 = mysqli_num_rows($result2); 

?>


<!DOCTYPE html>
<html>
<head>
<style>
table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
  width: 100%;
}
td, th {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}
</style>
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
<h2 class="text-center">Available RSOs</h2>
<table>
  <tr>
    <th>Name</th>
    <th>Status</th>
    <th>Description</th>
  </tr>
  <tbody>
  <?php foreach ($result as $row){ ?>
      <tr>
<td><?php echo ($row["name"]);?></td>
<td><?php echo ($row["status"]); ?></td>
<td><?php echo ($row["description"]); ?></td>
<td><form method="post">
<input type="submit" name="join" value="JOIN"  class="btn btn-primary text-center" style="margin-bottom: 30px;">         
    </form></td>
      </tr>
      <?php 
# Php code for each button
} ?>
      </tbody>
</table>
<br>
<br>

<h2 class="text-center">Your RSOs</h2>
<table>
  <tr>
    <th>Name</th>
    <th>Status</th>
    <th>Description</th>
  </tr>
  <tbody>
  <?php foreach ($result2 as $row) { ?>
      <tr> 
<td><?php echo ($row["name"]);?></td>
<td><?php echo ($row["status"]); ?></td>
<td><?php echo ($row["description"]); ?></td>

<td><form method="post">
<input type="submit" name="leave"  
value="LEAVE"  class="btn btn-primary text-center" style="margin-bottom: 30px;">     
    </form></td>
      </tr>
    <?php 
# Php code for each button

} ?>
      </tbody>
</table>
</body>
<br>
<br>
	<h1 class="text-center"><?php echo($_SESSION['userName']);?> </h1>
    <h1 class="text-center"><a href="http://localhost/Project/home">Home</a> </h1>
    <h1 class="text-center"><a href="http://localhost/Project/index">Log Out</a> </h1>
</html>












































