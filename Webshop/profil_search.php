<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Kereses</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php 
    if (session_status() === PHP_SESSION_DISABLED)
    session_start();
    include 'menu.php'; ?>
        <?php
            include "db.php";
            $link = getDb();

            if (empty($_POST['nev']) && !isset($_POST['osszes'])) {
                echo '<div class="message">Válasszon egy opciót!</div>';
                header("refresh: 2; url=profil_kereses.php");
                die;
            }

            if (isset($_POST['nev'])) {
                $nev = mysqli_real_escape_string($link, $_POST['nev']);
                $query = sprintf("SELECT Felhasznalo.Nev as Nev, Felhasznalo.Email as Email, Felhasznalo.Cim as Cim , Roles.RoleName as RoleName FROM Felhasznalo JOIN Roles where nev='%s'and Felhasznalo.RoleId=Roles.Id order by Nev asc", $nev);
                if (empty($_POST['nev']) || isset($_POST['osszes']))
                    $query = sprintf("SELECT Felhasznalo.Nev as Nev, Felhasznalo.Email as Email, Felhasznalo.Cim as Cim , Roles.RoleName as RoleName FROM Felhasznalo JOIN Roles where Felhasznalo.RoleId=Roles.Id order by Nev asc");
                $eredmeny = mysqli_query($link, $query) or die('<div class="message">Rossz a lekérdezés' . (mysqli_error($link)) . '</div>');
                if (mysqli_num_rows($eredmeny) > 0) {
        ?>

        <div class="container">
        <div class="row justify-content-center black-text">
            <table class="table table-striped table-hover table-bordered centered-table">
                <thead>
                    <tr>
                        <th>Név</th>
                        <th>Email</th>
                        <th>Cím</th>
                        <th>Privilégium szint</th>
                    </tr> 
                </thead>
                <tbody>
                    <?php while ($sor=mysqli_fetch_array($eredmeny)) : ?>   
                        <tr>
                            <td><?=$sor['Nev']?></td>
                            <td><?=$sor['Email']?></td>
                            <td><?=$sor['Cim']?></td>
                            <td><?=$sor['RoleName']?></td>
                        </tr>
                    <?php endwhile; ?>
                </tbody>
            </table>
        </div>
    </div>
    <?php 
    } else {
        echo '<div class="message">Nincs ilyen felhasználó az adatbázisban!</div>';
    }
} else {
    echo '<div class="message">Hiba a POST paraméterrel</div>';
}
mysqli_close($link);
include 'footer.php'; 
?>  
    </body>
</html>
