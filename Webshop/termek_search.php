<!DOCTYPE html>
<html>
    <head>
        <title>Kereses</title>   
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
        <link rel="stylesheet" href="header.css"> 
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" crossorigin="anonymous">
    </head>
    <body>
        <?php 
            if (session_status() === PHP_SESSION_DISABLED) {
                session_start();
            }

            include 'menu.php';
            include "db.php";

            $link= getDb();

            
            if(isset($_POST['nev']) or isset($_POST['kategoria']) and isset($_POST['uj'])) {

    $nev=mysqli_real_escape_string($link, $_POST['nev']);
    $kategoria=mysqli_real_escape_string($link, $_POST['kategoria']);
    $arkriterium=mysqli_real_escape_string($link, $_POST['ar']);
    if(isset($_POST['osszes']))
    $osszes=mysqli_real_escape_string($link, $_POST['osszes']);

    if($arkriterium=='option1')
    $sort_order = 'DESC';
    else if($arkriterium=='option2')
    $sort_order = 'ASC';


    if(!empty($nev) or !empty($kategoria)) {

        if(!empty($nev) and !empty($kategoria))
        $query= sprintf("SELECT * FROM Termek WHERE Nev='%s' AND Kategoria='%s' ORDER BY Ar $sort_order",$nev,$kategoria) or die(mysqli_error($link));

        else if(!empty($nev))
        $query= sprintf("SELECT * FROM Termek where Nev='%s' order by Ar $sort_order",$nev);

        else if(!empty($kategoria))
        $query= sprintf("SELECT * FROM Termek where Kategoria='%s' order by Ar $sort_order",$kategoria);

    }

    if(empty($nev) and empty($kategoria) and !isset($osszes))
    {
    echo  "<div class='message'> Töltse ki a név vagy a kategória mezőt! </div>" ;
    header("refresh:3; url=termek_kereses.php");
    die;
    }
 


    if(isset($osszes))
    $query= sprintf("SELECT * FROM Termek order by Ar $sort_order");

    $eredmeny=mysqli_query($link,$query);

    $num_rows=mysqli_num_rows($eredmeny);
    if($num_rows==0){
    echo "<div class='message'> Hibás párosítás </div>";
    header("refresh:3; url=termek_kereses.php");
    die;
}

?>


<div class="container">
<div class="row justify-content-center black-text">
        <table class="table table-striped table-hover table-bordered centered-table">
            <thead>
                <tr>
                    <th>Név</th>
                    <th>Ár</th>
                    <th>Darabszám</th>
                    <th>Kategória</th>
                    <?php if (isset($_SESSION['aktiv_felhasznaloId'])): ?>    <th>Kosárba</th> <?php endif; ?>
                </tr> 
            </thead>
            <tbody>
                <?php while ($sor=mysqli_fetch_array($eredmeny)) : ?>   
                    <tr>
                        <td><?=$sor['Nev']?></td>
                        <td><?=$sor['Ar']?></td>
                        <td><?=$sor['Db']?></td>
                        <td><?=$sor['Kategoria']?></td>
                        
                        <td>
                            <?php if (isset($_SESSION['aktiv_felhasznaloId'])): ?>
                                <form action="kosar.php" method="post">
                                    <input type="hidden" name="termekId" value="<?=$sor['Id']?>">
                                    <input type="number" name="darab" min="1" max="<?=$sor['Db']?>" value="1" class="darab-input">
                                    <button type="submit" name="add_to_kosar" class="btn btn-primary custom-button">
                                        <i class="fa fa-shopping-cart"></i>
                                    </button>
                                </form>
                            <?php endif; ?>
                        </td>
                    </tr>
                <?php endwhile; ?>
            </tbody>
        </table>
    </div>
</div>
<?php 
mysqli_close($link);
include 'footer.php'; 
} 
?>
</body>
</html>