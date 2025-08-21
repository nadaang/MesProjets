<?php

ob_start();
?>
    <form action="update.php" method="post">
    <input type="text" value="<?php echo $element->id ?>" name="id">

    <input type="date" value="<?php echo $element->date ?>"  name="date">
    <!--ici je peux mettre le type text et dnc je reçois le nom enregistré dans la BD-->
    <!--<input type="file" value="<?php echo $element->cv ?>"  name="cv">
    <input type="file" value="<?php echo $element->lettre ?>" name="lettre">
-->
    
    <div class="cv">
        <input type="file" value="<?php echo $element->cv ?>" name="cv">
        <div class="info">
        <i class="icon fa-solid fa-upload"></i>
        <span>Modifier votre cv</span>
        </div>
        </div>

        <div class="lettre">
        <input type="file" name="lettre" value="<?php echo $element->lettre ?>">
        <div class="info">
        <i class="icon fa-solid fa-upload"></i>
        <span>CHanger votre lettre de motivation</span>
                
                </div>
              </div>  
    
    
    
    
    
    <input type="submit" name="envoyer">

    </form>

<?php $contenu = ob_get_clean(); ?>


<?php include_once 'views/vue_principale.php'; ?>
