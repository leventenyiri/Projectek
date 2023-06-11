<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="header.css"> 
<?php include 'menu.php'; ?>

<div class="container form-container">
    <form method="post" class="my-4">
        <h1>Módosítani kívánt adatok:</h1>
        <?php
        include 'db.php';
        $link = getDb();

        list($felhasznaloId, $termekId, $regidatum) = explode('_', mysqli_real_escape_string($link, $_GET['id']));
        $regidatum = urldecode($regidatum);

        $jelenlegiQuery = sprintf("SELECT FelhasznaloId, TermekId, Darab, Datum 
                             FROM Rendeles 
                             WHERE Rendeles.FelhasznaloId='%d' AND Rendeles.TermekId='%d' AND Rendeles.Datum='%s'",
            mysqli_real_escape_string($link, $felhasznaloId),
            mysqli_real_escape_string($link, $termekId),
            mysqli_real_escape_string($link, $regidatum)
        );
        $jelenlegiEredmeny = mysqli_query($link, $jelenlegiQuery);
        $jelenlegiErtekek = mysqli_fetch_assoc($jelenlegiEredmeny);

        if (isset($_POST['uj'])) {

            if (!empty($_POST['db'])) {
                if (!is_numeric($_POST['db'])) {
                    echo '<div class="message">Hiba, a darabszámnak számnak kell lennie!</div>';
                    header("refresh: 2; url='rendelesek.php");
                    die;
                }
                $db = $_POST['db'];
            } else {
                $db = $jelenlegiErtekek['Darab'];
            }

            if (!empty($_POST['datum'])) {
                $datum = $_POST['datum'];
            } else {
                $datum = $jelenlegiErtekek['Datum'];
            }

            if (!empty($_POST['felhasznalo_id'])) {
                $ujfelhasznaloId = $_POST['felhasznalo_id'];
            } else {
                $ujfelhasznaloId = $jelenlegiErtekek['FelhasznaloId'];
            }

            if (!empty($_POST['termek_id'])) {
                $ujtermekId = $_POST['termek_id'];
            } else {
                $ujtermekId = $jelenlegiErtekek['TermekId'];
            }

            $query = sprintf("UPDATE Rendeles 
            SET FelhasznaloId='%d', TermekId='%d', Darab='%s', Datum='%s' 
            WHERE Rendeles.FelhasznaloId='%d' AND Rendeles.TermekId='%d' AND Rendeles.Datum='%s'",
                mysqli_real_escape_string($link, $ujfelhasznaloId),
                mysqli_real_escape_string($link, $ujtermekId),
                mysqli_real_escape_string($link, $db),
                mysqli_real_escape_string($link, $datum),
                mysqli_real_escape_string($link, $felhasznaloId),
                mysqli_real_escape_string($link, $termekId),
                mysqli_real_escape_string($link, $regidatum)
            );

            if (mysqli_query($link, $query)) {
                echo '<div class="message">Rendelés módosítva.</div>';
                header("refresh: 2; url= rendelesek.php");
            } else {
                echo '<div class="message">Error: ' . mysqli_error($link) . '</div>';
            }
            exit();
        }
        ?>
        <div class="form-group">
            <label for="felhasznalo_id">Kihez tartozzon?</label>
            <select name="felhasznalo_id" id="felhasznalo_id" class="form-control">
                <option value="">-- Válasszon egy felhasználót --</option>
                <?php
                $query = "SELECT Id, Nev FROM Felhasznalo";
                $eredmeny = mysqli_query($link, $query);
                while ($row = mysqli_fetch_assoc($eredmeny)) {
                    $selected = '';
                    if ($row['Nev'] == $_GET['nev']) {
                        $selected = 'selected';
                    }
                    echo "<option value=\"" . $row['Id'] . "\" $selected>" . $row['Nev'] . "</option>";
                }
                ?>
            </select>
        </div>

        <div class="form-group">
            <label for="termek_id">Termék:</label>
            <select name="termek_id" id="termek_id" class="form-control">
                <option value="">-- Válasszon egy terméket --</option>
                <?php
                $query = "SELECT Id, Nev FROM Termek";
                $eredmeny = mysqli_query($link, $query);
                while ($row = mysqli_fetch_assoc($eredmeny)) {
                    $selected = '';
                    if ($row['Nev'] == $_GET['nev']) {
                        $selected = 'selected';
                    }
                    echo "<option value=\"" . $row['Id'] . "\" $selected>" . $row['Nev'] . "</option>";
                }
                ?>
            </select>
        </div>

        <div class="form-group">
            <label for="db">Darabszám:</label>
            <input type="text" name="db" id="db" class="form-control" />
        </div>

        <div class="form-group">
            <label for="datum">Dátum:</label>
            <input type="datetime-local" name="datum" id="datum" class="form-control" />
        </div>

        <div class="form-group">
            <button type="submit" class="btn btn-primary custom-button" name="uj">Módosítás</button>  
        </div>
    </form>
</div>

<?php include 'footer.php'; ?>
