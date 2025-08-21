<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!--<link rel="stylesheet" href="style.css">-->
    <title>Document</title>
</head>
<body>


<?php ob_start(); ?>

<section id="consulter" class="affichage">
            
            <h4>Liste des candidatures</h4>
            <table>
                <tr>
                    <th>ID</th>
                    <th>Date de soumission</th>
                    <th>CV</th>
                    <th>Lettre de motivation</th>
                    <th>Update</th>
                    <th>Delete</th>
                    <th>Compétences</th>
                </tr>

                <tbody>
                <?php foreach ($elements as $element): ?>
            <tr>
                <td><?= $element->id ?></td>
                <td><?= $element->date ?></td>
                <td><?= $element->cv ?></td>
                <td><?= $element->lettre ?></td>
                <td><a href="delete.php?id=<?php echo $element->id ?>">supprimer</a></td>
                <td><a href="edit.php?id=<?php echo $element->id ?>">modifier</a></td>
           
            </tr>
        <?php endforeach; ?>
                </tbody>

            </table>

</section>



          

<?php $contenu = ob_get_clean(); ?>


<?php include_once 'vue_principale.php'; ?>
          

</body>
</html>
