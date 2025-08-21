#include "formations.h"
#include <QSqlQuery>
#include <QDebug>
#include<QObject>
#include<QDate>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QFileDialog>
Formations::Formations()
{

    id=0;
        nom="";
        //debut="";
        //fin="";
        //QDate debut; // Initialise debut à une date non définie (vide)
        // Par exemple, affecter la date du 1er janvier 2023 à debut
        //debut.setDate(2023, 1, 1);

        statut="";
        description="";
        organisme="";
        certif="";
        prix=0;
}


Formations::Formations(int i,QString n ,/*QString d,QString f*/QDate d,QDate f,QString s,QString des,QString o,QString c,int p)
{
    this->id=i;
    this->nom=n;
    this->debut=d;
    this->fin=f;
    this->statut=s;
    this->description=des;
    this->organisme=o;
    this->certif=c;
    this->prix=p;
}

bool Formations::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("insert into formations(id, nom, debut, fin, statut, description, organisme, certificat, prix)" "values(:id, :nom, :debut, :fin, :statut, :description, :organisme, :certif, :prix)");
    //query.bindValue(":id", id);
    query.bindValue(":id",id_string);
    query.bindValue(":nom",nom);
    query.bindValue(":debut",debut);
    query.bindValue(":fin",fin);
    query.bindValue(":statut",statut);
    query.bindValue(":description",description);
    query.bindValue(":organisme",organisme);
    query.bindValue(":certif",certif);
    query.bindValue(":prix",prix);
    return query.exec();

}


QSqlQueryModel * Formations::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel;

    model->setQuery("SELECT* from formations");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datedebut"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("datefin"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("statut"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("organisme"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("validité du certif"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("prix"));

    return model;
}


bool Formations::supprimer(int id)
{
        QSqlQuery query;
        QString id_string = QString::number(id);

        query.prepare("DELETE from formations where id= :id");

        query.bindValue(":id",id_string);

        return query.exec();
}


/*
bool Formations::modifier(int id, QString attribut, QString nouvelleValeur) {
    QSqlQuery query;
    QString id_string = QString::number(id);

    // Vérification de l'attribut à modifier pour préparer la requête en conséquence
    QString columnToModify;
    if (attribut == "nom") {
        columnToModify = "nom";
    } else if (attribut == "debut") {
        columnToModify = "debut";
    } else if (attribut == "fin") {
        columnToModify = "fin";
    }else if (attribut == "statut") {
        columnToModify = "statut";
    }else if (attribut == "organisme") {
        columnToModify = "organisme";
    }else if (attribut == "prix") {
        columnToModify = "prix";
    }

    query.prepare("UPDATE formations SET " + columnToModify + " = :nouvelleValeur WHERE id = :id");
    query.bindValue(":id", id_string);
    query.bindValue(":nouvelleValeur", nouvelleValeur);



    return query.exec();
}
ici debut/fin sont de type varchar2 ds sql je les ai changé de type data dans la fct suivante à cause du calendrier
*/




bool Formations::modifier(int id, QString attribut, QString nouvelleValeur) {
    QSqlQuery query;
    QString id_string = QString::number(id);

    // Vérification de l'attribut à modifier pour préparer la requête en conséquence
    QString columnToModify;
    QVariant valueToBind;

    if (attribut == "nom" || attribut == "statut" || attribut == "organisme") {
        columnToModify = attribut;
        valueToBind = nouvelleValeur;
    } else if (attribut == "debut" || attribut == "fin") {
        columnToModify = attribut;
        // Convertir la nouvelle valeur en objet QDate
        QDate date = QDate::fromString(nouvelleValeur, "dd-MM-yyyy");
        valueToBind = date;

    } else if (attribut == "prix") {
        columnToModify = "prix";
        valueToBind = nouvelleValeur.toDouble();
    } else {
        // Gérer d'autres types d'attributs ici selon vos besoins
        // ...
    }

    query.prepare("UPDATE formations SET " + columnToModify + " = :nouvelleValeur WHERE id = :id");
    query.bindValue(":id", id_string);
    query.bindValue(":nouvelleValeur", valueToBind);




    return query.exec();
}









bool Formations::rechercher(QString n)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM formations WHERE nom = :n");
    query.bindValue(":nom", n);
    return query.exec();

/*
    if(query.exec()){
    if (query.next()) {

            int id = query.value(0).toInt();
            QString nom = query.value(1).toString();
            return true;
            }
    }
    return false;*/
}



QSqlQueryModel *Formations::trier() {
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM formations ORDER BY debut ASC"); // ASC pour tri croissant et DESC pour décroissant
    return model;
/*
si debut ou fin etaient de type QString on fera:
QDate debutDate = QDate::fromString(debut, "yyyy-MM-dd"); pour la convertir en QDate puis SELECT * FROM formations ORDER BY debut ASC
Cette requete"ORDER BY" effectue le tri n'importe c quoi le type meme chaine juste ce qui est essentiel est que les données soient ttes stockées
sous la meme forme(exemple:yyyy-MM-dd)
*/

}



void Formations::exportToPDF(const QString &nomFichier) {
    // Effectuez la requête SQL pour obtenir les données des formations
    QSqlQueryModel model;
    model.setQuery("SELECT * FROM formations");

    // Créez un objet QPdfWriter pour générer le PDF
    QPdfWriter pdfWriter(nomFichier);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));

    // Créez un objet QPainter pour dessiner le contenu dans le PDF
    QPainter painter(&pdfWriter);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // Commencez la génération du PDF
    painter.begin(&pdfWriter);

    // Dessinez le contenu du PDF, par exemple, un tableau de données

    painter.drawText(100, 150, "\n\nID  |  Nom  |  Debut  |  Fin  |  Statut  |  Description  |  Organisme  |  Certificat  |  Prix\n");

    int y = 400;
    for (int row = 0; row < model.rowCount(); ++row) {
        QString id = model.data(model.index(row, 0)).toString();
        QString nom = model.data(model.index(row, 1)).toString();
        QString debut = model.data(model.index(row, 2)).toString();
        QString fin = model.data(model.index(row, 3)).toString();
        QString statut = model.data(model.index(row, 4)).toString();
        QString description = model.data(model.index(row, 5)).toString();
        QString organisme = model.data(model.index(row, 6)).toString();
        QString certificat = model.data(model.index(row, 7)).toString();
        QString prix = model.data(model.index(row, 8)).toString();

        QString ligne = id + "  |  " + nom + "  |  " + debut + "  |  " + fin + "  |  " +
                        statut + "  |  " + description + "  |  " + organisme + "  |  " +
                        certificat + "  |  " + prix + "\n";
        painter.drawText(100, y, ligne);
        y += 400; // Augmentez la valeur pour augmenter l'espacement entre les lignes.
    }

    // Terminez la génération du PDF
    painter.end();
}
