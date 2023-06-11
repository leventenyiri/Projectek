<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Termék törlése</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php
    include 'menu.php';
    include 'db.php';

    if (isset($_POST['nev']) and !empty($_POST['nev'])) {
        $link = getDb();
        $nev = mysqli_real_escape_string($link, $_POST['nev']);

        $query = "SELECT * FROM Termek WHERE Nev='" . $nev . "'";
        $eredmeny = mysqli_query($link, $query);
        $num_rows = mysqli_num_rows($eredmeny);

        if ($num_rows > 0) {
            $query1 = "DELETE FROM Rendeles WHERE TermekId=(SELECT Id FROM Termek WHERE Nev='" . $nev . "')";
            mysqli_query($link, $query1);

            $query2 = "DELETE FROM Termek WHERE Nev='" . $nev . "'";
            mysqli_query($link, $query2);

            echo "<div class='message'>" . $_POST['nev'] . " törölve lett!</div>";
        }

        mysqli_close($link);

        header("refresh:3; url=termek_torles.php");
        exit();
    } else {
        echo "<div class='message'>Válasszon egy opciót!</div>";
        header("refresh:3; url=termek_torles.php");
    }
    ?>
</body>
</html>
