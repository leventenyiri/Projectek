<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 

<?php
session_start();
require_once 'db.php';

include 'menu.php';

if (isset($_POST['uj'])) {
    $link = getDb();
    $nev = isset($_POST['felhasznalonevmod']) ? mysqli_real_escape_string($link, $_POST['felhasznalonevmod']) : '';
    $jelszo = isset($_POST['jelszo']) ? mysqli_real_escape_string($link, $_POST['jelszo']) : '';
    $email = isset($_POST['email']) ? mysqli_real_escape_string($link, $_POST['email']) : '';
    $regi_nev = $_SESSION['eredeti_felhasznalonevmod'] ?? '';
    $query = "UPDATE Felhasznalo SET ";
    $utca = isset($_POST['utca']) ? mysqli_real_escape_string($link, $_POST['utca']) : '';
    $varos = isset($_POST['varos']) ? mysqli_real_escape_string($link, $_POST['varos']) : '';
    $hazszam = isset($_POST['hazszam']) ? mysqli_real_escape_string($link, $_POST['hazszam']) : '';
    
    $cim = $varos . ',' . ' ' . $utca . ' ' . $hazszam . '.';

    if (isset($_POST['privilege']) and $_POST['privilege'] != '') {
        $privilegium = $_POST['privilege'];
    } else {
        $privilegium = null;
    }

    $fieldsToUpdate = [];
    if ($nev != '') {
        if (!preg_match("/^.{0,30}$/", $nev)) {
            echo '<div class="message">Hiba, a név maximum 30 karakter hosszú lehet!</div>';
            header("refresh: 2; url=profil_modositas.php");
            exit;
        }
        $fieldsToUpdate[] = sprintf("Nev='%s'", mysqli_real_escape_string($link, $nev));
    }

    if ($jelszo != '') {
        if (!preg_match("/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/", $jelszo)) {
            echo '<div class="message">A jelszónak legalább 8 karakter hosszúnak kell lennie, tartalmaznia kell legalább egy nagy és egy kisbetűt, valamint egy számot és egy speciális karaktert</div>';
            header("refresh: 2; url=profil_modositas.php");
            exit;
        }
        $hashedJelszo = password_hash($jelszo, PASSWORD_DEFAULT);
        $fieldsToUpdate[] = sprintf("Jelszo='%s'", mysqli_real_escape_string($link, $hashedJelszo));
    }

    if ($email != '') {
        if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            echo '<div class="message">Hibás email formátum!</div>';
            header("refresh: 2, url=profil_modositas.php");
            exit;
        }
        $fieldsToUpdate[] = sprintf("Email='%s'", mysqli_real_escape_string($link, $email));
    }

    if ($varos != '' and $utca != '' and $hazszam != '') {
        if (!preg_match("/^[a-zA-Z]+(?:[\s-][a-zA-Z]+)*$/", $varos, $utca)) {
            echo '<div class="message">Hibás város vagy utca mező!</div>';
            header("refresh: 2, url=profil_modositas.php");
            die;
        }
        if (!preg_match("/^\d+[a-zA-Z]?$/", $hazszam)) {
            echo '<div class="message">Hibás házszám!</div>';
            header("refresh: 2; url=profil_modositas.php");
            die;
        }
        $fieldsToUpdate[] = sprintf("Cim='%s'", mysqli_real_escape_string($link, $cim));
    }

    if ($privilegium !== null) {
        $fieldsToUpdate[] = sprintf("RoleId='%d'", mysqli_real_escape_string($link, $privilegium));
    }

    if (empty($fieldsToUpdate)) {
        echo '<div class="message">Adjon meg változtatni kívánt adatot!</div>';
        exit;
    }

    $query .= implode(", ", $fieldsToUpdate);
    $query .= sprintf(" WHERE Nev='%s'", mysqli_real_escape_string($link, $regi_nev));

    if (!mysqli_query($link, $query)) {
        echo '<div class="message">Error updating record: ' . mysqli_error($link) . '</div>';
    } else {
        echo '<div class="message">Módosítások elmentve!</div>';
        header("refresh: 2; url=profil_modositas_elokeszito.php");
    }

    mysqli_close($link);
} else {
    echo '<div class="message">Adjon meg változtatni kívánt adatot!</div>';
}
?>

<?php include 'footer.php'; ?>
