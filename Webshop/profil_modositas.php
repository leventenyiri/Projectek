<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 

<?php 
if (session_status() === PHP_SESSION_ACTIVE)
    session_start();
include 'menu.php'; 

if (isset($_POST['felhasznalonevmod']) && !empty($_POST['felhasznalonevmod'])) {
    $_SESSION['eredeti_felhasznalonevmod'] = $_POST['felhasznalonevmod'];
} else {
    $_SESSION['eredeti_felhasznalonevmod'] = NULL;
    echo '<div class="message">Válasszon egy opciót</div>';
    header("refresh: 2; url='profil_modositas_elokeszito.php");
    die;
}
?>

<div class="container form-container">
    <form action="profil_modify.php" method="post">
        <h1 class="mb-4">Módosítani kívánt adatok:</h1>
        <div class="form-group">
            <label for="felhasznalonevmod">Új név:</label>
            <input type="text" class="form-control" id="felhasznalonevmod" name="felhasznalonevmod">
        </div>
        <div class="form-group">
            <label for="jelszo">Új jelszó:</label>
            <input type="text" class="form-control" id="jelszo" name="jelszo">
            <small id="jelszoHelp" class="form-text text-muted">
                A jelszónak legalább 8 karakter hosszúnak kell lennie, tartalmaznia kell legalább egy nagy és egy kisbetűt, valamint egy számot és egy speciális karaktert!
            </small>
        </div>
        <div class="form-group">
            <label for="email">Új email:</label>
            <input type="text" class="form-control" id="email" name="email">
        </div>
        <div class="form-group">
            <label>Új cím:</label>
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
        <?php if($_SESSION['aktiv_role'] == 3): ?>
            <div class="form-group">
                <label for="privilege">Jogosultsági kör:</label>
                <select class="form-control" name="privilege">
                    <option value="">-- Válasszon egy jogosultsági kört --</option>
                    <?php
                    include 'db.php';
                    $link = getDb();
                    $query = "SELECT Id, Rolename FROM Roles";
                    $eredmeny = mysqli_query($link, $query);
                    while ($row = mysqli_fetch_assoc($eredmeny)) {
                        $selected = ($row['Id'] === $user['RoleId']) ? 'selected' : '';
                        echo "<option value=\"" . $row['Id'] . "\" $selected>" . $row['Rolename'] . "</option>";
                    }
                    ?>
                </select>
            </div>
        <?php endif; ?>
        <button type="submit" class="btn btn-primary custom-button" name="uj">Küldés</button>
    </form>
</div>

<?php include 'footer.php'; ?>
