<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css">
<?php
session_start();
include 'menu.php';
include 'db.php';

if (isset($_POST['nev'], $_POST['ar'], $_POST['db'], $_POST['kategoria'], $_POST['uj'])) {
    $link = getDb();
    $regi_nev = mysqli_real_escape_string($link, $_SESSION['eredeti_nev']);
    $query = "UPDATE Termek SET ";
    $updated_fields = array();

    if (!empty($_POST['nev'])) {
        if(!preg_match("/^[a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ]+(?:[\s-][a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ]+)*$/",$_POST['nev'])){
            echo "<div class='message'>Hiba, a név csak betűkből állhat!</div>";
            header("refresh: 2, url=termek_modositas_elokeszito.php");
            die;
        }
        $nev = mysqli_real_escape_string($link, $_POST['nev']);
        $query .= "Nev='$nev', ";
        $updated_fields['nev'] = $nev;
    }

    if (!empty($_POST['ar'])) {
        if (!is_numeric($_POST['ar'])) {
            echo "<div class='message'>Hiba, az árnak számnak kell lennie!</div>";
            header("refresh: 2; url=termek_modositas_elokeszito.php");
            die;
        }
        $ar = mysqli_real_escape_string($link, $_POST['ar']);
        $query .= "Ar='$ar', ";
        $updated_fields['ar'] = $ar;
    }

    if (!empty($_POST['db'])) {
        if (!is_numeric($_POST['db'])) {
            echo "<div class='message'>Hiba, a darabszámnak számnak kell lennie!</div>";
            header("refresh: 2; url=termek_modositas_elokeszito.php");
            die;
        }
        $db = mysqli_real_escape_string($link, $_POST['db']);
        $query .= "Db='$db', ";
        $updated_fields['db'] = $db;
    }

    if (!empty($_POST['kategoria'])) {
        if(!preg_match("/^[a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ]+(?:[\s-][a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ]+)*$/",$_POST['kategoria'])){
            echo "<div class='message'>Hiba, a kategória csak betűkből állhat!</div>";
            header("refresh: 2, url=termek_modositas_elokeszito.php");
            die;
        }
        $kategoria = mysqli_real_escape_string($link, $_POST['kategoria']);
        $query .= "Kategoria='$kategoria', ";
        $updated_fields['kategoria'] = $kategoria;
    }

    $query = rtrim($query, ', ');

    if (count($updated_fields) > 0) {
        
        $query .= " WHERE Nev='$regi_nev'";
        if (!mysqli_query($link, $query)) {
            echo "<div class='message'>Error updating record: " . mysqli_error($link) . "</div>";
        } else {
            echo "<div class='message'>Módosítások elmentve!</div>";
        }
    } else {
        echo "<div class='message'>Adjon meg változtatni kívánt adatot!</div>";
    }

    mysqli_close($link);
} else {
    echo "<div class='message'>Adjon meg változtatni kívánt adatot!</div>";
}

header("refresh:3; url=termek_modositas_elokeszito.php");
?>

<?php include 'footer.php'; ?>
