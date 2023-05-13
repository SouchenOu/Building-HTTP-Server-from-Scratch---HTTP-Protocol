<html lang="en">
<body style="background-color: blue; color: red;">
<div style="display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%;">
	<h1>Register using PHP-CGI</h1>


<?php
	if(isset($_GET["Your_name"]) || isset($_GET["Your_Age"]))
	{
		echo "Using the GET method to pass data<br/>";
		echo "Your name is ".$_GET["Your_name"].".<br/>";
		echo "Your Age is ".$_GET["Your_Age"].".<br/>";
	}
	else if(isset($_POST["Your_name"]) || isset($_POST["Your_Age"]))
	{
		echo "Using the POST method to pass data<br/>";
		echo "Your name is ".$_POST["Your_name"].".<br/>";
		echo "Your Age is ".$_POST["Your_Age"].".<br/>";
	}
?>

	<h2>Post Request</h2>
<form action="Register" method="post">
 	<p>Your FullName: <input type="text" name="Your_name" /></p>
 	<p>Your Age: <input type="text" name="Your_Age" /></p>
 	<p><input type="submit" /></p>
</form>

 	<h2>Get Request</h2>
 <form action="Register" method="get">
 	<p>Your FullName: <input type="text" name="Your_name" /></p>
 	<p>Your Age : <input type="text" name="Your_Age" /></p>
 	<p><input type="submit" /></p>
 </form>




</div>
</body>
</html>
