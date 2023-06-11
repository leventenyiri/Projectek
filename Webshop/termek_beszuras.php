<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Új termék</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php include 'menu.php'; ?>
    
    <div class="container form-container">
        <form action="termek_insert.php" method="post">
            <h1 class="mt-5">Új termék</h1>
            <div class="form-group">
                <label for="nev">Név:</label>
                <input type="text" class="form-control" id="nev" name="nev" required>
            </div>
            <div class="form-group">
                <label for="ar">Ár:</label>
                <input type="text" class="form-control" id="ar" name="ar" required>
            </div>
            <div class="form-group">
                <label for="darabszam">Darabszám:</label>
                <input type="text" class="form-control" id="darabszam" name="darabszam" required>
            </div>
            <div class="form-group">
                <label for="kategoria">Kategória:</label>
                <input type="text" class="form-control" id="kategoria" name="kategoria">
            </div>
            <button type="submit" class="btn btn-primary custom-button" id="uj" name="uj">Elküld</button>
        </form>
    </div>
</body>
<?php include 'footer.php'; ?>
</html>
