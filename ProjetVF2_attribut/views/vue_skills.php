<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!--<link rel="stylesheet" href="style.css">-->
    <title>Document</title>
</head>
<body>


<?php ob_start(); ?>

<section id="skills" class="affichage">  
                <!--là g enlevé form pr que ces inputs seront envoyés avec les précédents  --> 
                <form action="">
                <h5 ><a href="#skills" id="link_skill">Compétences</a></h5>
                <input id="idt2" type="text" placeholder="Identifiant" name="id_skill">

                <input type="text" placeholder="Nom" name="nom">

                <div class="choices">
                <label for="niveau">Niveau de Maîtrise :</label>
                <select id="niveau" name="niveau">
                    <option value="debutant">Débutant</option>
                    <option value="intermediaire">Intermédiaire</option>
                    <option value="avance">Avancé</option>
                </select>
                </div>

                <input type="text" placeholder="Description" name="description">
                
                <input type="button" value="Tout voir" class="btn_see_skills" onclick="window.location.href='see_skills.php';">





                <input type="submit" value="Enregister" class="add_btn">
                </form>
</section>



          


<?php $contenu = ob_get_clean(); ?>


<?php include_once 'vue_principale.php'; ?>
          

</body>
</html>
