<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 

<?php
if (session_status() === PHP_SESSION_DISABLED)
    session_start();
include 'menu.php'; 
include 'db.php';

if (isset($_POST['nev']) && isset($_POST['jelszo'])) {

    $link = getDb();

    $nev = mysqli_real_escape_string($link,$_POST['nev']);
    $jelszo = trim($_POST['jelszo']); 
    $jelszo = filter_var($jelszo, FILTER_SANITIZE_STRING);

   
    

    $query = sprintf("SELECT * FROM Felhasznalo WHERE nev='%s'", mysqli_real_escape_string($link, $nev));
    $eredmeny = mysqli_query($link, $query) or die('<div class="message">' . mysqli_error($link) . '</div>');

    /*$options = [
        'cost' => 12,
    ];
    echo password_hash("Adminjelszo8@", PASSWORD_BCRYPT, $options); // Más jelszó beállításához még jól jöhet */

    if (mysqli_num_rows($eredmeny) == 1) {
        $row = mysqli_fetch_assoc($eredmeny);

        if (password_verify($jelszo, $row['Jelszo'])) {
            $_SESSION['aktiv_felhasznaloId'] = $row['Id'];
            $_SESSION['aktiv_felhasznalonev'] = $nev;
            $_SESSION['aktiv_role'] = $row['RoleId'];
            header('Location: index.php');
            exit;
        } else {
            echo '<div class="message">Helytelen felhasználónév vagy jelszó!</div>';
            header('refresh: 2; url=profil_bejelentkezes.php');
        }
    } else {
        echo '<div class="message">Helytelen felhasználónév vagy jelszó!</div>';
        header('refresh: 2; url=profil_bejelentkezes.php');
        die;
    }
}

mysqli_close($link);
?>

<?php include 'footer.php'; ?>