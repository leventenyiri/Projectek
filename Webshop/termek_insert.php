<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Termék beszúrás</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">

</head>
<body>
    <?php 
    include 'menu.php';
    include 'db.php'; 

    if(isset($_POST['uj']) and isset($_POST['nev']) and isset($_POST['ar']) and isset($_POST['darabszam'])){
        $link = getDb();
        $nev = mysqli_real_escape_string($link,$_POST['nev']);
        $ar = mysqli_real_escape_string($link,$_POST['ar']);
        $dbszam = mysqli_real_escape_string($link,$_POST['darabszam']);
        $kategoria = mysqli_real_escape_string($link,$_POST['kategoria']);

        if(empty($nev) or empty($ar) or empty($dbszam)) {
            echo "<div class='message'>Hiba, üresen hagyott mező!</div>";
            header("refresh: 2; url=termek_beszuras.php");
            die;
        } 
        
        if(!preg_match("/^[a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ ]*$/",$nev) or !preg_match("/^[a-zA-ZáéíóöőúüűÁÉÍÓÖŐÚÜŰ ]*$/",$kategoria)){
            echo "<div class='message'>Hiba, a név és a kategória csak betűket tartalmazhat!</div>";
            header("refresh: 2; url=termek_beszuras.php");
            die;
        }
        
        if(!is_numeric($ar) or !is_numeric($dbszam)){
            echo "<div class='message'>Hiba, az ár és a darabszám csak számokat tartalmazhat!</div>";
            header("refresh: 2; url=termek_beszuras.php");
            die;
        }

        $query = sprintf("SELECT * FROM Termek WHERE nev='%s'", mysqli_real_escape_string($link, $nev));
        $result = mysqli_query($link, $query);
        if(mysqli_num_rows($result) > 0) {
            echo "<div class='message'>Hiba, a termék már létezik a rendszerben!</div>";
            header("refresh: 2; url=termek_beszuras.php");
            die;
        }

        $query = sprintf("INSERT INTO Termek(nev,ar,db,kategoria) VALUES ('%s','%d','%d','%s')",
            mysqli_real_escape_string($link, $nev),
            mysqli_real_escape_string($link, $ar),
            mysqli_real_escape_string($link, $dbszam),
            mysqli_real_escape_string($link, $kategoria));

        mysqli_query($link, $query) or die("Hiba".mysqli_error($link));

        mysqli_close($link);
        
        echo "<div class='message'; >Termék hozzáadva</div>";
        header("refresh: 2; url=termek_beszuras.php");
        exit;
    }
    else {
        echo "<div class='message'>Hiba, üresen hagyott mező!</div>";
    }
    ?>

    <?php include 'footer.php'; ?>
</body>
</html>
