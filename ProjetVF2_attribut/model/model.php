<?php

    function connexion(){
        return new PDO('mysql:dbname=projet_devweb;host=localhost', 'root', '');
    }


    function send_data(){
        // Récupération des données du formulaire
        $id = $_POST['id'];
        $date = $_POST['date'];
        
        $nom_fichier_cv = $_FILES['cv']['name'];
        $temp_name_cv = $_FILES['cv']['tmp_name'];
        $taille_fichier_cv = $_FILES['cv']['size'];
    
        $nom_fichier_lettre = $_FILES['lettre']['name'];
        $temp_name_lettre = $_FILES['lettre']['tmp_name'];
        $taille_fichier_lettre = $_FILES['lettre']['size'];
    
        // Vérification et traitement du fichier CV
        if(isset($nom_fichier_cv) && !empty($nom_fichier_cv)) {
            $dossier = "uploads/";
            $nom_final_fichier_cv = $id . "_cv_" . $nom_fichier_cv;
            if(move_uploaded_file($temp_name_cv, $dossier . $nom_final_fichier_cv)) {
                echo "Le fichier CV a été téléchargé avec succès.";
            } else {
                echo "Erreur lors du téléchargement du fichier CV.";
            }
        } else {
            echo "Aucun fichier CV n'a été téléchargé.";
        }
    
        // Vérification et traitement du fichier Lettre
        if(isset($nom_fichier_lettre) && !empty($nom_fichier_lettre)) {
            $dossier = "uploads/";
            $nom_final_fichier_lettre = $id . "_lettre_" . $nom_fichier_lettre;
            if(move_uploaded_file($temp_name_lettre, $dossier . $nom_final_fichier_lettre)) {
                echo "Le fichier Lettre a été téléchargé avec succès.";
            } else {
                echo "Erreur lors du téléchargement du fichier Lettre.";
            }
        } else {
            echo "Aucun fichier Lettre n'a été téléchargé.";
        }
    
        // Connexion à la base de données et insertion des données dans la table 'candidatures'
        $pdo = connexion();
        $sqlstate = $pdo->prepare('INSERT INTO candidatures (id, date, cv, lettre) VALUES (?, ?, ?, ?)');
        $sqlstate->execute([$id, $date, $nom_final_fichier_cv, $nom_final_fichier_lettre]);
    }


    function get_data(){
        $pdo = connexion();
        return $pdo->query('SELECT * FROM candidatures')->fetchAll(PDO::FETCH_OBJ);
    }

    function delete_data($id){
        $pdo = connexion();
        $sqlstate = $pdo->prepare('DELETE FROM candidatures WHERE id = ?');
        $sqlstate->execute([$id]);
    }


    function edit_data($id){
        $pdo = connexion();
        $sqlstate = $pdo->prepare('SELECT * FROM candidatures WHERE id = ?');
        $sqlstate->execute([$id]);
        return $sqlstate->fetch(PDO::FETCH_OBJ);
    }


    function update_data ($id,$date, $cv, $lettre){
        $pdo = connexion();
        $sqlstate = $pdo->prepare('UPDATE candidatures SET date = ?, cv = ?, lettre = ? WHERE id =?');
        $sqlstate->execute([$date, $cv, $lettre,$id]);
      //l'id est inchangeable peut etre car c where id=
    }

/*
    function get_id(){
        $pdo = connexion();
         // Requête SQL pour récupérer le dernier ID
         $sql = "SELECT MAX(id) AS dernier_id FROM votre_table";
         $stmt = $pdo->prepare($sql);
         $stmt->execute();
 
         // Récupérer le dernier ID
         $row = $stmt->fetch(PDO::FETCH_ASSOC);
         $dernierId = $row['dernier_id'];
 
 
         // Retourner le dernier ID
         return $dernierId;
    }*/




?>
