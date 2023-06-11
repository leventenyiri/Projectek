<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Termék módosítása</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php 
    if (session_status() === PHP_SESSION_DISABLED)
    session_start();
    include 'menu.php';  

    if (isset($_POST['nev']) && !empty($_POST['nev'])) {
        $_SESSION['eredeti_nev'] = $_POST['nev'];
    } else {
        $_SESSION['eredeti_nev'] = NULL;
        echo "<div class='message'>Válassz egy opciót</div>";
        header("refresh: 2; url=termek_modositas_elokeszito.php");
        die;
    }
    ?>
    
    <div class="container form-container">
        <form action="termek_modify.php" method="post">
            <h1 class="mt-5">Módosítani kívánt adatok:</h1>
            <p>
                Új név: <input type="text" name="nev" class="form-control"/>    
            </p>
            <p>
                Új ár: <input type="text" name="ar" class="form-control"/>
            </p>
            <p>
                Új darabszám: <input type="text" name="db" class="form-control"/>
            </p>
            <p>
                Új kategória: <input type="text" name="kategoria" class="form-control"/>
            </p>
            <p>
                <input type="submit" value="Küldés" name="uj" class="btn btn-primary custom-button"/>
            </p>
        </form>
    </div>
    
    
</body>
<?php include 'footer.php'; ?>
</html>
