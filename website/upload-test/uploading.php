<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Uploading files, images...</title>
</head>
<body style="background-color: violet; color: yellow;">

<h1>Uploading using CGI</h1>
<h2>Select file or image to upload...</h2>


<div style="display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%;">
    <form action="uploading.php" method="post" enctype="multipart/form-data">
     
        <Input type="file" name="image" />

        <Input type="submit" value="Upload file"/>

    </form>


</div>
</body>
</html>