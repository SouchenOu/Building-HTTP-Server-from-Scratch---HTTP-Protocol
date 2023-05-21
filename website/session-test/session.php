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
$_SESSION["userID"] = "ouchen";
$_SESSION["password"] = "soukaina";
echo "<br>PHP Session is established and session variables are set successfully!\n";
?>

<?php
// Echo session variables that were set on previous page
echo "My user ID is " . $_SESSION["userID"] . ".<br>";
echo "My password is " . $_SESSION["password"] . ".";
?>
</body>
</html>