<?php
/*
$dossier='doc/'; //dossier ou sera déplacé le fichier
$nom_temporaire=$_FILES['fichier']['tmp_name'];
if(!is_uploaded_file($nom_temporaire))//indique si le fichier a été téléchargé par HTTP POST
{exit("le fichier est introuvable");}
//on copie le fichier dans le dossier destination
$nom_fichier=$_FILES['fichier']['name'];
if(move_uploaded_file($nom_temporaire,$dossier.$nom_fichier))
{
    header("location:http://local:7882/fichier/doc/");

}
else{
    exit("impo de copier le fichier dans $dossier");
}
*/



/*
if(isset($_POST['submit'])){
    $id=$_POST['id']
    $date=$_POST['date']
    $cv=$_POST['cv']
    $lettre=$_POST['lettre']

    if(isset($_FILES['cv']) and $_FILES['cv']['error']==0)
    {
        $dossier='doc/';
        $temp_name=$_FILES['cv']['tmp_name'];
        if(!is_uploaded_file($temp_name))
        {
            exit('fichier introuvable');
        }
        if($_FILES['cv']['size']>= 1000000){
            exit('erreur, le fichier est volumineux');
        }

        $infosfichier = pathinfo($_FILES['cv']['name']);
        $extension_upload = $infosfichier['extension'];

        $extension_upload = strtolower($extension_upload);
        $extension_autorisees = array('png','jpeg','jpg');
        if(!in_array($extension_upload, $extension_autorisees))
        {
            exit('err, inserer un fichier avec extensions autorisees')
        }
        $nom_fichier=$id.".".$extension_upload;
        if(!move_uploaded_file($temp_name, $dossier.$nom_fichier)){
            exit("prob ds le telecharg");
        }
        $ph_name = $nom_fichier;
    }

    $requette = "INSERT INTO candidatures Values('$id', '$date', '$cv', '$lettre')";
    $resultat = mysqli_query($link,$requette);

    

    header('location: afficher.php');
}*/

require_once 'controller/controller.php';
store();


?>