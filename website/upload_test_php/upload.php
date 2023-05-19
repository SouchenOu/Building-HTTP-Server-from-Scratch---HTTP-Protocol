<html lang="en">
<body style="background-color: blue; color: red;">
<div style="display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%;">
	<h1>upload using PHP-CGI</h1>


<?php
// Check if the form was submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
  // Specify the directory where uploaded files will be saved
  $target_dir = "uploads/";

  // Loop through each file input and upload the file if it was selected
  for ($i = 1; $i <= 4; $i++) {
    if (!empty($_FILES["file$i"]["name"])) {
      $target_file = $target_dir . basename($_FILES["file$i"]["name"]);
      $uploadOk = 1;
      $imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

      // Check if the file already exists
      if (file_exists($target_file)) {
        echo "Sorry, file already exists.";
        $uploadOk = 0;
      }

      // Check file size
      if ($_FILES["file$i"]["size"] > 5000000) {
        echo "Sorry, your file is too large.";
        $uploadOk = 0;
      }

      // Allow certain file formats
      if($imageFileType != "jpg" && $imageFileType != "jpeg" && $imageFileType != "png" && $imageFileType != "pdf" && $imageFileType != "mp4") {
        echo "Sorry, only JPG, JPEG, PNG, and PDF files are allowed.";
        $uploadOk = 0;
      }

      // Check if $uploadOk is set to 0 by an error
      if ($uploadOk == 0) {
        echo "Sorry, your file was not uploaded.";
      } else {
        if (move_uploaded_file($_FILES["file$i"]["tmp_name"], $target_file)) {
          echo "The file ". htmlspecialchars(basename($_FILES["file$i"]["name"])). " has been uploaded.";
        } else {
          echo "Sorry, there was an error uploading your file.";
        }
      }
    }
  }
}
?>
<h1>File Uploader</h1>
    <p>Select up files to upload</p>
  </header>
  <main>
    <form action="upload_test_php" method="post" enctype="multipart/form-data">
      <div class="form-group">
        <label for="file1">File 1</label>
        <input type="file" name="file1" id="file1" accept=".jpg, .jpeg, .png, .pdf, .mp4" required>
      </div>
      <button type="submit">Upload Files</button>
    </form>
  </main>
</body>
</html>