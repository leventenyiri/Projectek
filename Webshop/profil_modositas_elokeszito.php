<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 
<?php 
if (session_status() === PHP_SESSION_ACTIVE)
session_start();
include 'menu.php'; 
?>
<div class="container">
    <div class="centered-content2">
        <form class="my-5 centered-form" action="profil_modositas.php" method="post">
            <h1>Profil módosítása</h1>
            <div class="form-group">
                <label for="felhasznalonevmod">Felhasználó név:</label>
                <select class="form-control" name="felhasznalonevmod" id="felhasznalonevmod">
                    <option value="">-- Válasszon egy felhasználót --</option>
                    <?php
                    include 'db.php';
                    $link = getDb();
                    $query = "SELECT Nev FROM Felhasznalo";
                    $eredmeny = mysqli_query($link, $query);
                    while ($row = mysqli_fetch_assoc($eredmeny)) {
                        echo "<option value=\"" . $row['Nev'] . "\">" . $row['Nev'] . "</option>";
                    }
                    ?>
                </select>
            </div>
            <button type="submit" class="btn btn-primary custom-button" name="uj">Küldés</button>
        </form>
    </div>
</div>

<?php include 'footer.php'; ?>
