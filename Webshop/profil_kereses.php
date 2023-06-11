<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 

<?php include 'menu.php'; ?>

<div class="container form-container">
    <form action="profil_search.php" method="post">
        <h1>Keresés felhasználók között</h1>
        <div class="form-group">
            <label for="nev">Név:</label>
            <select class="form-control" name="nev" id="nev">
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

        <div class="form-row">
            <div class="form-group col">
                <button type="submit" class="btn btn-primary custom-button" name="uj">Keresés</button>
            </div>
            <div class="form-group col">
                <button type="submit" class="btn btn-primary custom-button" name="osszes">Összes mutatása</button>
            </div>
        </div>
    </form>
</div>

<?php include 'footer.php'; ?>
