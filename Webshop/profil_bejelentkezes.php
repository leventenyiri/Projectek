<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 

<?php include 'menu.php'; ?>

<div class="container form-container">
    <form action="profil_login.php" method="post">
        <h1>Adja meg a nevét és jelszavát!</h1>
        <div class="form-group">
            <label for="nev">Felhasználónév:</label>
            <input type="text" name="nev" id="nev" class="form-control" />
        </div>
        <div class="form-group">
            <label for="jelszo">Jelszó:</label>
            <input type="password" name="jelszo" id="jelszo" class="form-control" />
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-primary custom-button" name="uj">Bejelentkezés</button>
        </div>
    </form>
</div>

<?php include 'footer.php'; ?>
