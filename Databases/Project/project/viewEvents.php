<?php
require_once('connect.php');			 
session_start(); 				
if ($_SESSION['userID'] == -1) {		
    header("Location: http://localhost/Project/index");
}

if (array_key_exists('comments', $_POST)) {
  $_SESSION["event_id"] = $_POST['eventId'];
  header("Location: http://localhost/Project/comments");
}



if (isset($_POST['submit'])) {
    /*if (array_key_exists("comments", $_POST)) {
      # $_SESSION["event_id"] = $_POST['eventId'];
      header("Location: http://localhost/Project/comments");
  
    }*/


    //require "connect.php";
    $category = $_POST['category'];
    if ($category == "Public") { // show all public events
      $sql = "Select * from event where category='Public'";
      $result = mysqli_query($conn, $sql);

    } else if ($category == "Private") {
      $school = $_SESSION['school'];
      $sql = "Select * from event where (category='Private' AND school ='$school')";
      $result = mysqli_query($conn, $sql);
    } else if ($category == "RSO") {
      $userId = $_SESSION['userID'];
      $sql = "SELECT * FROM event Where (event.category='RSO' AND event.event_id IN (SELECT createevent.event_id FROM createevent WHERE createevent.RSO_id IN (Select apart.RSO_id from apart where apart.user_id = '$userId')))";
      $result = mysqli_query($conn, $sql);
    }

    $sql = "Select * from event where category='$category'";
    /*$Events = "select * 
			   from event 
			   where event_id = (select event_id from RSO_event where RSO_id = (select RSO_id from apart where user_id = '$user_id'))
			   OR event_id = (select event_id from private_event where school = '$school')
			   OR event_id = (select event_id from public_event)"; */
    
	  $num = mysqli_num_rows($result);
  }

?>

<!--------------------------------HTML--------------------------------------------->

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
<h2 class="text-center">Choose a Category to display associated events</h2> <br>
<small id="emailHelp" class="form-text text-muted text-center">
			Public - Public events near your Location
			</small>
      <small id="emailHelp" class="form-text text-muted text-center">
			Private - Private events on your College Campus
			</small>
      <small id="emailHelp" class="form-text text-muted text-center">
			RSO - Private events hosted by your Registered Student Organization
			</small> <br>

<form method="post" class="text-center">
    <div class="input-field">
        <input required type="number" name="eventId" placeholder="Enter eventId" autocomplete="off">
      
        <input type="submit" name="comments" class="button" value="Comments" />
		</div>
</form>

<form method="post" class="text-center">
  <label for="category"class="text-center">Category:</label>
  <select name="category" id="category" class="text-center">
        <option value="Public">All public events </option>
        <option value="Private">Student only events</option>
        <option value="RSO">Only events from organazations you are a member of</option>                               
    </select>
  <input type="submit" name="submit" class="text-center">
  
</form>


<?php
if (isset($_POST['submit'])) {
  if ($result && $num > 0) { ?>
    <h2>Events</h2>

    <table>
      <thead>
<tr>
<th>Event ID</th>
<th>Category</th>
  <th>School</th>
  <th>Event Name</th>
  <th>Description</th>
  <th>Email Address</th>
  <th>Contact Number</th>
  <th>Location</th>
  <th>Date</th>
</tr>
      </thead>
      <tbody>
  <?php foreach ($result as $row) { ?>
      <tr>
<td><?php echo ($row["event_id"]); ?></td>
<td><?php echo "<b>".$row["category"]."</b>"; ?>&nbsp;</td>
<td><?php echo ($row["school"]); ?></td>
<td><?php echo ("<b>".$row["name"]."</b>"); ?></td>
<td><?php echo ($row["description"]); ?></td>
<td><?php echo ("<b>".$row["email"]."</b>"); ?></td>
<td><?php echo ($row["phone"]."</b>"); ?></td>
<td><?php echo ("<b>".$row["location"]);?></td>
<td><?php echo ($row["date_time"]."</b>");?></td>
    
    
    <?php 
  } ?>
  </td>

      </tr>



      
      </tbody>
  </table>

   
  <?php } else { ?>
    > No results found for <?php echo ($_POST['category']); ?>.
  <?php }
} ?>
<h1 class="text-center"><?php echo($_SESSION['userName']);?> </h1>
<h1 class="text-center"><a href="home.php">Home</a></h1>
<h1 class="text-center"><a href="http://localhost/Project/index">Log Out</a> </h1>
