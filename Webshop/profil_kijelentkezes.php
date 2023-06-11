<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="library.css"> 
<?php include 'menu.php'; 

session_start();
$_SESSION['aktiv_felhasznalonev']=NULL;
$_SESSION['aktiv_felhasznaloId']=NULL;
$_SESSION['aktiv_role']=NULL;
header("Location: index.php");


?>