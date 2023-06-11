<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Új felhasználó létrehozása</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php include 'menu.php'; ?>
    
    <div class="container form-container">
        <form action="profil_insert.php" method="post">
            <h1 class="mt-5">Új felhasználó létrehozása</h1>
            <div class="form-group">
                <label for="nev">Felhasználónév:</label>
                <input type="text" class="form-control" name="nev" id="nev" />
            </div>
            <div class="form-group">
                <label for="jelszo">Jelszó:</label>
                <input type="text" class="form-control" name="jelszo" id="jelszo" />
                <small id="jelszoHelp" class="form-text text-muted">
                    A jelszónak legalább 8 karakter hosszúnak kell lennie, tartalmaznia kell legalább egy nagy és egy kisbetűt, valamint egy számot és egy speciális karaktert!
                </small>
            </div>
            <div class="form-group">
                <label for="email">E-mail:</label>
                <input type="text" class="form-control" name="email" id="email" />
            </div>
            <div class="form-group">
                <label>Cím:</label>
                <div class="form-row">
                    <div class="col">
                        <input type="text" class="form-control" name="varos" placeholder="Város" />
                    </div>
                    <div class="col">
                        <input type="text" class="form-control" name="utca" placeholder="Közterület" />
                    </div>
                    <div class="col">
                        <input type="text" class="form-control" name="hazszam" placeholder="Házszám" />
                    </div>
                </div>
            </div>
            <button type="submit" class="btn btn-primary custom-button" name="uj">Elküld</button>
        </form>
    </div>
    <?php include 'footer.php'; ?>
</body>
</html>
