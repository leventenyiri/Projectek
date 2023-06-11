<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous"> 
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" crossorigin="anonymous">
<link rel="stylesheet" href="header.css">

<?php
if (session_status() === PHP_SESSION_DISABLED)
    session_start();

include "menu.php";
include "db.php";
$link = getDb();

if (!isset($_SESSION['kosar'])) {
    $_SESSION['kosar'] = array();
}

// Kosárhoz adás
if (isset($_POST['add_to_kosar'])) {
    $termekId = mysqli_real_escape_string($link,($_POST['termekId']));
    $darab = mysqli_real_escape_string($link,($_POST['darab']));

    if (isset($_SESSION['kosar'][$termekId])) {
        $_SESSION['kosar'][$termekId]['darab'] += $darab;
    } else {
        $_SESSION['kosar'][$termekId] = [
            'darab' => $darab,
            'FelhasznaloId' => $_SESSION['aktiv_felhasznaloId'], 
            'TermekId' => $termekId,
            'Datum' => date('Y-m-d H:i:s') 
        ];
    }
    
    header("Location: termek_kereses.php");
}

$allResults = [];

foreach ($_SESSION['kosar'] as $termekId => $item) {
    $query = sprintf(
        "SELECT * FROM Termek WHERE Id = '%s'",
        mysqli_real_escape_string($link, $termekId)
    );
    $eredmeny = mysqli_query($link, $query) or die(mysqli_error($link));
    $termek = mysqli_fetch_assoc($eredmeny);
    $termek['FelhasznaloId'] = $item['FelhasznaloId'];
    $termek['TermekId'] = $item['TermekId'];
    $termek['Datum'] = $item['Datum'];
    $termek['darab'] = $item['darab']; 

    $allResults[] = $termek;
}

if (isset($_POST['checkout'])) {
    $validOrder = true;

    foreach ($_SESSION['kosar'] as $termekId => $item) {
        $queryTermek = sprintf("SELECT Termek.Db, Termek.Nev FROM Termek WHERE Id='%s'", mysqli_real_escape_string($link, $termekId));
        $termekEredmeny = mysqli_query($link, $queryTermek);
        $termekData = mysqli_fetch_assoc($termekEredmeny);
        $termekDarabszam = $termekData['Db'];
        $termekNev = $termekData['Nev'];
        $darab = $item['darab'];

        if ($termekDarabszam < $darab) {
            echo "<div class='message'> A $termekNev termékből csak $termekDarabszam darab van raktáron </div>";
            $validOrder = false;
            header("refresh: 2; url=kosar.php");
            die;
        }
    }

    // Ha minden termék darabszám kritériuma rendben van folytatjuk
    if ($validOrder) {
        foreach ($_SESSION['kosar'] as $termekId => $item) {
            $felhasznaloId = $_SESSION['aktiv_felhasznaloId'];
            $darab = $item['darab'];
            $queryTermek = sprintf("UPDATE Termek SET Db='%d' WHERE Id='%s'", mysqli_real_escape_string($link, ($termekDarabszam-$darab)), mysqli_real_escape_string($link, $termekId));
            mysqli_query($link, $queryTermek);

            $query = sprintf(
                "INSERT INTO Rendeles (FelhasznaloId, TermekId, Datum, Darab) VALUES ('%s', '%s', NOW(), '%s')",
                mysqli_real_escape_string($link, $felhasznaloId),
                mysqli_real_escape_string($link, $termekId),
                mysqli_real_escape_string($link, $darab)
            );
            mysqli_query($link, $query) or die(mysqli_error($link));
        }
    }

    $_SESSION['kosar'] = array();

    if ($validOrder) {
        echo "<div class='message'> Rendelés sikeresen leadva! </div>";
        header("refresh: 2; url=kosar.php");
    }
}


if (empty($allResults)) {
    echo " <div class='message'> Nincs semmi a kosárban. </div>";
    die;
}
?>

<div class="container">
    <div class="row justify-content-center black-text">
        <table class="table table-striped table-hover table-bordered centered-table">
            <thead>
                <tr>
                    <th>Név</th>
                    <th>Ár</th>
                    <th>Darabszám</th>
                    <th>Kategória</th>
                    <th>Összesen</th>
                    <th>Rendelés dátuma</th>
                    <th>Művelet</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($allResults as $sor) :
                    if ($sor != null) :
                ?>
                <tr>
                    <td><?= $sor['Nev'] ?></td>
                    <td><?= $sor['Ar'] ?></td>
                    <td><?= $sor['darab'] ?></td>
                    <td><?= $sor['Kategoria'] ?></td>
                    <td><?=$sor['darab']*$sor['Ar'] ?></td>
                    <td><?= $sor['Datum'] ?></td>
                    <td><a href='kosar_delete.php?id=<?= $sor['FelhasznaloId'] ?>_<?= $sor['TermekId'] ?>'><i class='fa fa-trash' style='font-size: 38px; color: #006400'></i></a></td>
                </tr>
                <?php
                        endif;
                    endforeach;
                ?>
            </tbody>
        </table>
    </div>
</div>

<form action="kosar.php" method="post" class="text-center">
    <button type="submit" name="checkout" class="btn btn-success btn-lg custom-button">Rendelés leadása</button>
</form>

<?php include 'footer.php'; 
mysqli_close($link);?>
