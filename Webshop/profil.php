<!DOCTYPE html>
<html>
    <head>
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" crossorigin="anonymous">
        <link rel="stylesheet" href="header.css">
    </head>
    <body>
        <?php include 'menu.php'; ?>
        <div class="centered-content2">
            <div class="centered-container2">
                <div class="container">

                    <?php if (!isset($_SESSION['aktiv_felhasznaloId'])): ?>
                        <div class="row centered-row">
                            <div class="col-sm">
                                <a href="profil_letrehozas.php" class="nav-link">Regisztráció <i class="fa fa-plus"></i></a>
                            </div>
                        </div>
                    <?php endif; ?>

                    <?php if (isset($_SESSION['aktiv_role']) && ($_SESSION['aktiv_role'] == 1 or $_SESSION['aktiv_role'] == 3)): ?>
                        <div class="row centered-row">
                            <div class="col-sm">
                                <a href="profil_letrehozas.php" class="nav-link">Új felhasználó létrehozása <i class="fa fa-plus"></i></a>
                            </div>
                        </div>
                    <?php endif; ?>

                    <?php if (isset($_SESSION['aktiv_felhasznalonev'])): ?>
                        <div class="row centered-row">
                            <div class="col-sm">
                                <a href="profil_kijelentkezes.php" class="nav-link">Kijelentkezés <i class="fa fa-user"></i></a>
                            </div>
                        </div>
                    <?php else: ?>
                        <div class="row centered-row">
                            <div class="col-sm">
                                <a href="profil_bejelentkezes.php" class="nav-link">Bejelentkezés <i class="fa fa-user"></i></a>
                            </div>
                        </div>
                    <?php endif; ?>

                    <?php if (isset($_SESSION['aktiv_role']) && ($_SESSION['aktiv_role'] == 1 || $_SESSION['aktiv_role'] == 3)): ?>
                        <div class="row centered-row">
                            <div class="col-sm">
                                <a href="profil_torles.php" class="nav-link">Felhasználó törlése <i class="fa fa-trash"></i></a>
                            </div>
                        </div>
                        <div class="row centered-row">
                            <div class="col-sm">
                                <a href="profil_modositas_elokeszito.php" class="nav-link">Felhasználó adatainak módosítása <i class="fa fa-wrench"></i></a>
                            </div>
                        </div>
                        <div class="row centered-row">
                            <div class="col-sm">
                                <a href="profil_kereses.php" class="nav-link">Keresés felhasználók között <i class="fa fa-search"></i></a>
                            </div>
                        </div>
                    <?php endif; ?>

                </div>
            </div>
        </div>
    </body>
</html>
