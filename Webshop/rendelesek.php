<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" crossorigin="anonymous">
<link rel="stylesheet" href="header.css">
<!DOCTYPE html>
<html>
<style>
  .row:nth-child(even) {
    background-color: #f2f2f2;
  }
</style>
<div class="container">
    
<head>
        <title>Rendelések</title>   
    </head>
    <body>
<?php 


    if(isset($_POST['osszes'])){
        header("Location: rendelesek.php");
        die;
    }
    
    include 'menu.php';
    include "db.php";
    $link= getDb();
    $name = isset($_POST['nev']) && !empty($_POST['nev']) ? mysqli_real_escape_string($link,$_POST['nev']) : null;

    //Ezek majd a dropdown listhez kellenek
    $select_query = "SELECT DISTINCT Felhasznalo.Nev as Nev FROM Felhasznalo";
    $select_result = mysqli_query($link, $select_query) or die("Rossz a lekérdezés" . (mysqli_error($link)));

    if(isset($name) and !empty($name))
    $query=sprintf("SELECT Rendeles.FelhasznaloId as FelhasznaloId, Rendeles.TermekId as TermekId, Rendeles.Datum as Datum, Felhasznalo.Nev as Felhasznalonev, Termek.Nev as Nev, Termek.Ar as Ar, Rendeles.Darab as Db, Termek.Kategoria as Kategoria FROM Termek join Felhasznalo join Rendeles where Rendeles.FelhasznaloId = Felhasznalo.Id and Rendeles.TermekId = Termek.Id and Felhasznalo.Nev = '%s'", mysqli_real_escape_string($link, $name));
    else
    $query=sprintf("SELECT Rendeles.FelhasznaloId as FelhasznaloId, Rendeles.TermekId as TermekId, Rendeles.Datum as Datum, Felhasznalo.Nev as Felhasznalonev, Termek.Nev as Nev, Termek.Ar as Ar, Rendeles.Darab as Db, Termek.Kategoria as Kategoria FROM Termek join Felhasznalo join Rendeles where Rendeles.FelhasznaloId = Felhasznalo.Id and Rendeles.TermekId = Termek.Id");

    $eredmeny= mysqli_query($link, $query) or die("Rossz a lekérdezés" . (mysqli_error($link)));

    
    if (mysqli_num_rows($eredmeny) == 0) {
        echo "<div class= message> Nincs jelenleg egy aktív rendelés sem. </div>";
        header("refresh: 2;url='rendelesek.php");
        die;
    }



?>


<div class="container">
        <div class="row justify-content-center black-text">
            <div class="col-lg-8">
        <table class="table table-striped table-hover table-bordered centered-table mb-0">      
    <thead>
        <tr>
            <th>Felhasználónév</th>
            <th>Név</th>
            <th>Ár</th>
            <th>Darabszám</th>
            <th>Kategória</th>
            <th>Rendelés dátuma</th>
        </tr> 
    </thead>
    <tbody>
        <?php while ($sor=mysqli_fetch_array($eredmeny)) : ?>   
            <?php if($sor != null) : ?>
                <tr>
                    <td><?=$sor['Felhasznalonev']?></td>
                    <td class="name-column"><?=$sor['Nev']?></td>
                    <td><?=$sor['Ar']?></td>
                    <td><?=$sor['Db']?></td>
                    <td><?=$sor['Kategoria']?></td>
                    <td><?=$sor['Datum']?></td>
                    <td><a href="rendelesek_delete.php?id=<?=$sor['FelhasznaloId']?>_<?=$sor['TermekId']?>_<?=urlencode($sor['Datum'])?>"><i class="fa fa-trash " style='font-size: 25px; color: #006400'></i></a></
                    <td><a href="rendelesek_modositas.php?id=<?=$sor['FelhasznaloId']?>_<?=$sor['TermekId']?>_<?=urlencode($sor['Datum'])?>"><i class="fa fa-wrench" style='font-size: 25px; color: #006400'></i></a></td>
                </tr>
            <?php endif; ?>
        <?php endwhile; ?>
    </tbody>
</table>
</div>
            <div class="col-lg-4">
            <form class="centered-form" action="rendelesek.php" method="post">
    <div class="form-group">
        <label for="nev" class="rendelesszoveg">Adott felhasználó rendelései:</label>
        <select class="form-control" id="nev" name="nev">
            <option value="">-- Válasszon felhasználót --</option>
            <?php while ($sor=mysqli_fetch_array($select_result)) : ?>
                <option value="<?=$sor['Nev']?>"><?=$sor['Nev']?></option>
            <?php endwhile; ?>
        </select>
    </div>
    <div class="form-group">
        <input type="submit" class="btn btn-success custom-button" value="Keresés" name="kereses" />
    </div>
    <div class="form-group">
        <input type="submit" class="btn btn-success custom-button" value="Összes" name="osszes" />
    </div>
</form>

</div>
        </div>
    </div>
</body>
</html>

<?php include 'footer.php'; 
mysqli_close($link);?>
