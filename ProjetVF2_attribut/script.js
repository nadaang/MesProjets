/*var postuler = document.getElementById("link1");
var idfield = document.getElementById("idt");

postuler.addEventListener("click", function(){
    var uniqueId = Date.now();
    idfield.value = uniqueId;
});*/

/*

document.addEventListener("DOMContentLoaded", function() {

    var postuler = document.getElementById("link1");
    var idfield = document.getElementById("idt");
    
    postuler.addEventListener("click", function(event){

        event.preventDefault(); // Empêcher le comportement par défaut du lien

        var uniqueId = Date.now();
        idfield.value = uniqueId;
    });
});


var submit  = document.getElementById("submit");*/

/*
document.addEventListener("DOMContentLoaded", function() {
    var postuler = document.getElementById("link1");
    var idfield = document.getElementById("idt");
    
    postuler.addEventListener("click", function(event){
        // Vérifier si l'ID a déjà été mis à jour
        if (!idUpdated) {
            event.preventDefault(); // Empêcher le comportement par défaut du lien

            // Mettre à jour l'ID
            var uniqueId = Date.now();
            idfield.value = uniqueId;

            // Mettre à jour la variable pour indiquer que l'ID a été mis à jour
            idUpdated = true;
        } else {
            // Si l'ID a déjà été mis à jour, permettre la navigation normale
            // Vous pouvez également rediriger vers une autre page ici
            // Par exemple :
            window.location.href = "autrepage.html";
        }
    });
});*/

//******************************************** */
/*
document.addEventListener("DOMContentLoaded", function() {
    var idfield = document.getElementById("idt");
   // var idAffiche = false; // Variable pour suivre si l'identifiant a déjà été affiché

    idfield.addEventListener("click", function() {
        //if (!idAffiche) {
            var uniqueId = Date.now();
            idfield.value = uniqueId;
           // idAffiche = true; // Mettre à true une fois que l'identifiant est affiché
        //}
    });
});*/


/*
document.addEventListener("DOMContentLoaded", function() {
    var idField = document.getElementById("idt2");
    var idAffiche = false; // Variable pour suivre si l'identifiant a déjà été affiché
    var idGenerer = null; // Variable pour stocker la valeur de l'identifiant généré

    idField.addEventListener("click", function() {
        if (!idAffiche) {
            idGenerer = <?php echo get_id() + 1; ?>; // Commencer l'identifiant à partir de 1
            idField.value = idGenerer;
            idAffiche = true; // Mettre à true une fois que l'identifiant est affiché
        } else {
            idField.value = idGenerer; // Ne pas changer la valeur une fois qu'elle est affichée
        }
    });
});*/




