<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Termék keresés</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php include 'menu.php'; ?>
    <div class="container form-container">
    <form action="termek_search.php?osszes=true" method="post" class="container">
        <h1 class="mt-5 text-dark-green">Termék keresés</h1>
        <p>
            Név: 
            <select name="nev" class="form-control">
                <option value="">-- Válasszon egy terméket --</option>
                <?php
                include 'db.php';
                $link = getDb();
                $query = "SELECT Nev FROM Termek";
                $eredmeny = mysqli_query($link, $query);
                while ($row = mysqli_fetch_assoc($eredmeny)) {
                    echo "<option value=\"" . $row['Nev'] . "\">" . $row['Nev'] . "</option>";
                }
                ?>
            </select>
        </p>
        <p>
            Kategória:
            <select name="kategoria" class="form-control">
                <option value="">-- Válasszon egy kategóriát --</option>
                <?php
                $query = "SELECT distinct Kategoria FROM Termek";
                $eredmeny = mysqli_query($link, $query);
                while ($row = mysqli_fetch_assoc($eredmeny)) {
                    echo "<option value=\"" . $row['Kategoria'] . "\">" . $row['Kategoria'] . "</option>";
                }
                mysqli_close($link);
                ?>
            </select>
        </p>
        <p>
            Rendezés:
            <select name="ar" class="form-control">
                <option value="option1"> Legdrágább elöl </option>
                <option value="option2"> Legolcsóbb elöl </option>
            </select>
        </p>
        <p>
            <input type="submit" value="Kiválasztás" name="uj" class="btn btn-primary custom-button" />
        </p>
        <p>
            <input type="submit" value="Összes kiírása" name="osszes" class="btn btn-primary custom-button" />
        </p>
    </form>
            </div>
            
</body>
<?php include 'footer.php'; ?>
</html>
