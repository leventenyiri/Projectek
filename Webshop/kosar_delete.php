<?php
if (session_status() === PHP_SESSION_NONE) {
    session_start();
}

include "db.php";
$link = getDb();

if (!isset($_GET['id'])) {
    echo '<div class="message">Hiba a termék azonosításában!</div>';
    die;
}

if (!isset($_SESSION['kosar'])) {
    echo '<div class="message">A kosár üres!</div>';
    die;
}

$id = explode('_', $_GET['id']);
$felhasznaloId = ($id[0]);
$termekId = ($id[1]);

unset($_SESSION['kosar'][$termekId]);

header("Location: kosar.php");
?>

<?php include 'footer.php'; 
mysqli_close($link);?>
