<?php 
if (session_status() !== PHP_SESSION_ACTIVE)
    session_start();
?>
<div class="container">
    <nav class="navbar navbar-expand-lg ">
        <a class="navbar-brand" href="index.php">Abu Csípős Bazára</a>
        <ul class="navbar-nav mr-auto">
            <li class="nav-item">
                <a href="termekek.php" class="nav-link">Termékek</a>
            </li>
            <li class="nav-item">
                <a href="kosar.php" class="nav-link">Kosár</a>
            </li>
            <li class="nav-item">
                <a href="profil.php" class="nav-link">Profil</a>
            </li>
            <?php if(isset($_SESSION['aktiv_role']) and (($_SESSION['aktiv_role'] == 1) or ($_SESSION['aktiv_role'] == 3))) { ?>
            <li class="nav-item">
                <a href="rendelesek.php" class="nav-link">Rendelések kezelése</a>
            </li>
            <?php } ?>
        </ul>
        <span class="navbar-text">
            <?php
            if(isset($_SESSION['aktiv_felhasznalonev'])) {
                echo "Aktív felhasználó: " . $_SESSION['aktiv_felhasznalonev'];
            }
            ?>
        </span>
    </nav>
</div>
