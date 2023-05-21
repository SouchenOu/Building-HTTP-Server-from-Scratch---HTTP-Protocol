<!DOCTYPE html>
<html>
<head>
	<title>Cookie Example</title>
    <script type="text/javascript" src="set_cookie.php"></script>
</head>
<body>
	<?php
	if(isset($_COOKIE["username"])) {
	    $username = $_COOKIE["username"];
	    echo "<h1>Welcome back, $username!</h1>";
	} else {
	    echo "<h1>Hello, we've set a cookie for you!</h1>";
	}
	
	?>
</body>
</html>