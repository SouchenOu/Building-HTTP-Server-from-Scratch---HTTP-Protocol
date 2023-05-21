<?php
// Start the PHP session
session_start();
?>
<!DOCTYPE html>
<html>
   <head>
      <title>PHP Session - Create</title>
   </head>
<body>
<?php
// Set session variables
$_SESSION["userID"] = "soukaina";
$_SESSION["password"] = "webserv";
echo "<br>PHP Session is established and session variables are set successfully!";
?>
</body>
</html>