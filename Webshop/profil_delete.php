<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 

<?php
include 'db.php';
include 'menu.php';

if (empty($_POST['nev'])) {
    echo '<div class="message"> Kérem válasszon egy opciót! </div>';
    header("refresh: 2; url=profil_torles.php");
    die;
}

if (isset($_POST['nev']) && !empty($_POST['nev'])) {
    $link = getDb();
    $nev = mysqli_real_escape_string($link, $_POST['nev']);

    $query = "SELECT * FROM Felhasznalo WHERE Nev='" . $nev . "'";
    $eredmeny = mysqli_query($link, $query);

    $query1 = "DELETE FROM Rendeles WHERE FelhasznaloId=(SELECT Id FROM Felhasznalo WHERE Nev='" . $nev . "')";
    mysqli_query($link, $query1);

    $query2 = "DELETE FROM Felhasznalo WHERE Nev='" . $nev . "'";
    mysqli_query($link, $query2);

    echo '<div class="message">' . $_POST['nev'] . " Törölve lett!" . '</div>';

    header("refresh: 2; url=profil_torles.php");

    mysqli_close($link);
}
?>

<?php include 'footer.php'; ?>
