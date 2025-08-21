<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>



<?php ob_start(); ?>

<section id="postuler">
    <form action="stocker.php" method="post" enctype="multipart/form-data">

        <input value="<?php generate_id();?>" id="idt" type="text" name="id" placeholder="Identifiant">
        <input type="date" name="date" >
                
        <div class="cv">
        <input type="file" name="cv">
        <div class="info">
        <i class="icon fa-solid fa-upload"></i>
        <span>Télécharger votre cv</span>
        </div>
        </div>

        <div class="lettre">
        <input type="file" name="lettre">
        <div class="info">
        <i class="icon fa-solid fa-upload"></i>
        <span>Poser votre lettre de motivation</span>
                
                </div>
              </div>  
            
              
        <h5 ><a href="skills.php" id="link_skill">Compétences</a></h5>

        <input id="submit" name='submit' type="submit" value="Ajouter" class="add_btn">            
                                      
    </form>
</section> 

<?php $contenu = ob_get_clean(); ?>

<?php include_once 'vue_principale.php'; ?>


</body>
</html>