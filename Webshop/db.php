<?php 

function getDb() {

    $link=mysqli_connect("localhost","root","")
    or die;
    mysqli_select_db($link, "webshop");
    mysqli_query($link ,"set character_set_results='utf8'"); 
    return $link;

}

?>