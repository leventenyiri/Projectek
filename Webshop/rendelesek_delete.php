<?php 
    include 'db.php';
    $link = getDb();

    if(isset($_GET['id'])) {
        list($felhasznaloId, $termekId, $datum) = explode('_', mysqli_real_escape_string($link, $_GET['id']));
        $query = "DELETE FROM Rendeles WHERE TermekId=$termekId AND FelhasznaloId=$felhasznaloId AND Datum='$datum'";
        mysqli_query($link, $query);
        Header("Location: rendelesek.php");
    }
    mysqli_close($link);
?>
