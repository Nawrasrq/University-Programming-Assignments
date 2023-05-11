<?php
// start of Code required to be logged in
require('connect.php');
session_start(); // get stored values
if ($_SESSION['userID'] == -1) {
    header("Location: http://localhost/Project/index");
}


$user_id = $_SESSION["userID"];
$event_id = $_SESSION['event_id'];

$sql = "Select * from comments where event_id='$event_id'";
$result = mysqli_query($conn, $sql);
$num = mysqli_num_rows($result);

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
<h1 class = "text-center"></h1>
<?php
 if ($result && $num > 0) { ?>
    <h2>Events</h2>
    <table>
      <thead>
	<tr>
	<th>User ID</th>
	<th>Rating</th>
	<th>Comment</th>
	<th>Timestamp</th>
	</tr>
      </thead>
      <tbody>
  <?php foreach ($result as $row) { ?>
      <tr>
<td><?php echo ($row["user_id"]); ?></td>
<td><?php echo "<b>".$row["rating"]."</b>"; ?>&nbsp;</td>
<td><?php echo ($row["text"]); ?></td>
<td><?php echo ("<b>".$row["timestamp"]."</b>"); ?></td>

       
    <?php 
  } ?>

      </tr>
      
      </tbody>
  </table>

   
  <?php } else { ?>
    No comments, be the first to post!.
  <?php 
  }
	
?>
</div>

<h1 class="text-center"><?php echo($_SESSION['userName']);?> </h1>
<h1 class="text-center"><a href="home.php">Home</a></h1>
<h1 class="text-center"><a href="http://localhost/Project/index">Log Out</a> </h1>