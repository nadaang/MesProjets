#ifndef FORMATIONS_H
#define FORMATIONS_H


#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
//#include <QDate>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QDate>

class Formations
{
    QString nom,statut,description,organisme,certif;
        int id,prix;
        QDate debut,fin;
public:
    Formations();
        //Formations(int,QString,QString,QString,QString,QString,QString,QString,int); //c nrmlment pour que qd on fait laffichage donc apporter des données

        Formations(int,QString,/*QString d,QString f*/QDate d,QDate f,QString, QString, QString, QString ,int );

        //getters
        QString getnom(){return nom;}
        //QString getdebut(){return debut;}
        //QString getfin(){return fin;}

        QDate getdebut(){return debut;}
        QDate getfin(){return fin;}

        QString getstatut(){return statut;}
        QString getdescription(){return description;}
        QString getorganisme(){return organisme;}
        QString getcertif(){return certif;}

        int getid(){return id;}
        int getprix(){return prix;}

        //setters
        void setnom(QString n){nom=n;}
        //void setdebut(QString d){debut=d;}
        //void setfin(QString f){fin=f;}

        void setdebut(QDate d){debut=d;}
        void setfin(QDate d){debut=d;}

        void setstatut(QString s){statut=s;}
            void setdescription(QString des){description=des;}
            void setorganisme(QString o){organisme=o;}
            void setcertif(QString c){certif=c;}

            void setid(int i){this->id=i;}
            void setprix(int p){prix=p;}


            //fonctionnalités
            bool ajouter();
            QSqlQueryModel * afficher();
            bool supprimer(int);
            bool modifier(int id, QString attribut, QString nouvelleValeur);
            bool rechercher(QString);
            QSqlQueryModel * trier();
            void exportToPDF(const QString &nomFichier);



};

#endif // FORMATIONS_H
