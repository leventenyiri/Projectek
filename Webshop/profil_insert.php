<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 

<?php 
include 'menu.php';
include 'db.php'; 

if (isset($_POST['uj']) && isset($_POST['nev']) && isset($_POST['jelszo']) && isset($_POST['email']) && isset($_POST['varos']) && isset($_POST['utca']) && isset($_POST['hazszam'])) {

    $link = getDb();
    mysqli_set_charset($link, "utf8");

    $nev = $_POST['nev'];
    $jelszo = trim($_POST['jelszo']);
    $jelszo = filter_var($jelszo, FILTER_SANITIZE_STRING);
    $hashedJelszo = password_hash($jelszo, PASSWORD_DEFAULT);

    $email = mysqli_real_escape_string($link,$_POST['email']);
    $varos = mysqli_real_escape_string($link,$_POST['varos']);
    $utca = mysqli_real_escape_string($link,$_POST['utca']);
    $hazszam = mysqli_real_escape_string($link,$_POST['hazszam']);
    $cim = $varos .', '. $utca .' '. $hazszam .'.';   

    if (empty($nev) or empty($jelszo) or empty($email) or empty($cim)) { 
        echo '<div class="message">Hiba, üresen hagyott mező!</div>';
        header("refresh: 2; url=profil_letrehozas.php");
        die;
    }

    if (!preg_match("/^.{0,30}$/", $nev)) {
        echo '<div class="message">Hiba, a név maximum 30 karakter hosszú lehet!</div>';
        header("refresh: 2; url=profil_letrehozas.php");
        die;
    }

    if (!preg_match("/^[a-zA-Z0-9+._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/", $email)) {
        echo '<div class="message">Hibás email formátum!</div>';
        header("refresh: 2, url=profil_letrehozas.php");
        die;
    }

    if (!preg_match("/^(?=.*[a-záéíóöőúüű])(?=.*[A-ZÁÉÍÓÖŐÚÜŰ])(?=.*\d)(?=.*[@$!%*?&])[A-Za-záéíóöőúüűÁÉÍÓÖŐÚÜŰ\d@$!%*?&]{8,}$/", $jelszo)) {
        echo '<div class="message">A jelszónak legalább 8 karakter hosszúnak kell lennie, tartalmaznia kell legalább egy nagy és egy kisbetűt, valamint egy számot és egy speciális karaktert</div>';
        header("refresh: 2; url=profil_letrehozas.php");
        die;
    }

    if (!preg_match("/^[a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ]+(?:[\s-][a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ]+)*$/", $varos, $utca)) {
        echo '<div class="message">Hibás város vagy utca mező!</div>';
        header("refresh: 2, url=profil_letrehozas.php");
        die;
    }

    if (!preg_match("/^\d+[a-zA-Z]?$/", $hazszam)) {
        echo '<div class="message">Hibás házszám!</div>';
        header("refresh: 2; url=profil_letrehozas.php");
        die;
    }
    
    $query = sprintf("SELECT * FROM Felhasznalo WHERE nev='%s'", mysqli_real_escape_string($link, $nev));
    $result = mysqli_query($link, $query) or die(mysqli_error($link));
    if (mysqli_num_rows($result) > 0) {
        echo '<div class="message">Hiba, a felhasználó már létezik a rendszerben!</div>';
        header("refresh: 2; url=profil_letrehozas.php");
        die;
    }

    $query = sprintf("INSERT INTO Felhasznalo(nev, jelszo, email, cim, RoleId) VALUES ('%s', '%s', '%s', '%s', 2)",
        mysqli_real_escape_string($link, $nev),
        mysqli_real_escape_string($link, $hashedJelszo),
        mysqli_real_escape_string($link, $email),
        mysqli_real_escape_string($link, $cim));

    mysqli_query($link, $query) or die("Hiba".mysqli_error($link));

    mysqli_close($link);

    echo '<div class="message">Felhasználó létrehozva!</div>';
    header("refresh: 2; url=index.php");

    exit;
} else {
    echo '<div class="message">Hiba, üresen hagyott mező!</div>';
}
?>

<?php include 'footer.php'; ?>
