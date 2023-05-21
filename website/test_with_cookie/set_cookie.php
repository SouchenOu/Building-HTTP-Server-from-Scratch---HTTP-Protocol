<?php
if (isset($_POST['user'])) {
    if (!isset($_COOKIE['user'])) {
        setcookie("user",  $_POST['user']);
        echo "<h1>Cookie was set with user={$_POST['user']}</h1>";
    }else {
        echo "<h1>Cookie is already set</h1>";
    }
} else {
    echo "<h1>please enter user name</h1>";
}
?>