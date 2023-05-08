<html lang="en">
<head>
   
</head>
<body style="background-color: red; color: yellow;">

<h1>Uploading using CGI</h1>

<div style="display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%;">

   <form action="upload.php" method="POST" enctype="multipart/form-data">
         <input type="file" name="image" />
         <input type="submit"/>
   </form>



</div>
</body>
</html>