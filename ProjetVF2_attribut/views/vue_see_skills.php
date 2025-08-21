<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!--<link rel="stylesheet" href="style.css">-->
    <title>Document</title>
</head>
<body>


<?php ob_start(); ?>

<section id="tt_voir" class="affichage">
            
            <h4>Liste des compétences</h4>
            <table>
                <tr>
                    <th>ID</th>
                    <th>Nom</th>
                    <th>Niveau de maitrise</th>
                    <th>Description</th>
                    <th>Update</th>
                    <th>Delete</th>
                </tr>

                <tbody>
                    <tr>
                        <td>1</td>
                        <td>777</td>
                        <td>8888</td>
                        <td>vvvv</td>
                        <td><button>Update</button></td>
                        <td><button>Delete</button></td>
                    </tr>
                </tbody>

            </table>

</section>



          


<?php $contenu = ob_get_clean(); ?>


<?php include_once 'vue_principale.php'; ?>
          

</body>
</html>