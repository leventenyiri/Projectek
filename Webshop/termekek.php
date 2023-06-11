<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" crossorigin="anonymous">
    <link rel="stylesheet" href="header.css">
</head>
<body>
    <?php 
    include 'menu.php'; 
    if (session_status() === PHP_SESSION_DISABLED)
        session_start();
    ?>

    <div class="centered-content">
        <div class="container centered-container ">
            <?php if(isset($_SESSION['aktiv_role']) && ($_SESSION['aktiv_role'] == 1 or $_SESSION['aktiv_role'] == 3)){ ?>
            <div class="row centered-row">
                <div class="col-sm">
                    <a href="termek_beszuras.php" class="nav-link no-hover-box">Termék hozzáadása <i class="fa fa-plus"></i></a>
                </div>
            </div>
            <div class="row centered-row">
                <div class="col-sm">
                    <a href="termek_torles.php" class="nav-link no-hover-box">Termék törlése <i class="fa fa-trash"></i></a>
                </div>
            </div>
            <div class="row centered-row">
                <div class="col-sm">
                    <a href="termek_modositas_elokeszito.php" class="nav-link no-hover-box">Termék módosítása <i class="fa fa-wrench"></i></a>
                </div>
            </div>
            <?php } ?>
            <div class="row centered-row">
                <div class="col-sm">
                    <a href="termek_kereses.php" class="nav-link no-hover-box">Termék keresése <i class="fa fa-search"></i></a>
                </div>
            </div>
        </div>
    </div>
</body>
</html>
