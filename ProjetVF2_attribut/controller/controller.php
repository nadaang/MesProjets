<?php 

    //require_once 'views/vue_principale.php'; //la sol pr le prob d'inclusion des 
    // fichiers et donc de 'undefined variable' => ne pas inclure ce fichier ici
    // ala khater ena amalt l'inclusion bch f index k n3ayet lel controller
    // ahawka f wostou la vue principale mais de cette façon plus tard bch yabda
    //ya9ra w bch yabda bel vue principale elly feha $content benesba liih non
    // déclarée khater mezel mawsolch lel appel mtae create() ou y'a l'integ
    // du fichier vue_create()
    require_once 'model/model.php';
    
        function test(){
            $x = connexion();
            echo "cnx réussie à la BD";
        }


        function main(){
            require_once 'views/vue_principale.php';
        }

        function create(){
            require_once 'views/vue_create.php';
        }

        function create_skills(){
            require_once 'views/vue_skills.php';
        }

        function afficher(){
            $elements = get_data();
            require_once 'views/vue_afficher.php';
        }

        function see_skills(){
            require_once 'views/vue_see_skills.php';
        }


        function store(){
            send_data();
            require_once 'index.php';
        }
        

        function delete(){
    
            $id = $_GET['id'];//fazzet supp lkol f get  w fel href w lview inutile à moins que bch taamel zeyed
            delete_data($id);
            require_once 'index.php';
        }

        
        
        function edit(){
            $id = $_GET['id'];
            $element= edit_data($id);
            require_once 'views/vue_edit.php';
        }




        function update(){
            $id = $_POST['id'];
            $date = $_POST['date'];
            $cv = $_POST['cv'];
            $lettre = $_POST['lettre'];
            update_data ($id,$date, $cv, $lettre);
            require_once 'index.php';
        }

        /*
        function generate_id(){
            $last_id=get_id();
            $nouvel_id= $last_id + 1;
            echo $nouvel_id;
        }*/
       

?>