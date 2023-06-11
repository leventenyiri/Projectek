<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Termék törlése</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php include 'menu.php'; ?>
    <div class="container form-container">
    <form action="termek_delete.php" method="post" class="container">
        <h1 class="mt-5 text-dark-green">Termék törlése</h1>
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
                mysqli_close($link);
                ?>
            </select>
        </p>
        <p>
            <input type="submit" value="Törlés" name="uj" class="btn btn-primary custom-button">
        </p>
        
    </form>
            </div>
            <?php include 'footer.php'; ?>
</body>
</html>
