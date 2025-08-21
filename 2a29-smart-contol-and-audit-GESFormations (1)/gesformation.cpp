#include "gesformation.h"
#include "ui_gesformation.h"
#include "formations.h"
#include "QDate"
#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QDialogButtonBox>
#include "serialcommunication.h"
#include "arduino.h"
gesformation::gesformation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gesformation),
    configDialog(new QDialog(this)),//configDialog est un pointeur vers un objet de type QDialog. Le paramètre this passé au constructeur de QDialog indique que le parent de ce nouveau QDialog est l'objet MainWindow. Cela signifie que lorsque MainWindow est détruit, il détruira également configDialog.
            dateTimeEditConfig(new QDateTimeEdit(configDialog))
{
    ui->setupUi(this);
    connect(ui->rappel, &QPushButton::clicked, this, &gesformation::on_pushButtonConfig_clicked);
        // formations.cpp (dans le constructeur Formations)




        // Setup ConfigDialog
            configDialog->setWindowTitle("Configurer la notification");
            configDialog->setModal(true);

            QVBoxLayout *layout = new QVBoxLayout(configDialog);
            layout->addWidget(dateTimeEditConfig);
            QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            connect(buttonBox, &QDialogButtonBox::accepted, configDialog, &QDialog::accept);
            connect(buttonBox, &QDialogButtonBox::rejected, configDialog, &QDialog::reject);
            layout->addWidget(buttonBox);

            dateTimeEditConfig->setDateTime(QDateTime::currentDateTime()); // Set initial value to current date and time




        chargerDatesColorees();  // Chargez les dates colorées au démarrage de l'application

            // ...

            connect(ui->calendrier, SIGNAL(selectionChanged()), this, SLOT(on_calendrier_selectionChanged()));

            chargerCalendrierAvecDatesColorees();  // Chargez les dates colorées dans le calendrier

            // Connectez le signal clicked du calendrier à la fonction mettreAJourTableView
                connect(ui->calendrier, SIGNAL(clicked(const QDate&)), this, SLOT(mettreAJourTableView(const QDate&)));



        ui->liste->setModel(f.afficher());
        ui->liste->resizeColumnsToContents();


        ui->editID->setValidator(new QIntValidator(0, 101, this));

        connect(buttonBox, &QDialogButtonBox::accepted, this, &gesformation::handleOkButton);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &gesformation::handleCancelButton);

        /*connect(&serialcommunication, &SerialCommunication::readyRead,
                    &serialcommunication, &SerialCommunication::readData);*/

      //  SerialCommunication serialCommunication; // Créez une instance de SerialCommunication
        // Utilisez cette instance pour accéder à 'serial' et effectuer la connexion
        //connect(serialCommunication.getSerial(), &QSerialPort::readyRead, &serialCommunication, &SerialCommunication::readData);



}

void gesformation::on_pushButtonConfig_clicked()
{
    configDialog->exec();
}


gesformation::~gesformation()
{
    delete ui;
}


void gesformation::on_ajouter_clicked()
{

    int id= ui->editID->text().toInt();
    QString nom= ui->editnom->text();

    //QString debut= ui->editdebut->text();
    //QString fin= ui->editfin->text();

    QDate debut=QDate::fromString(ui->editdebut->text(), "dd-MM-yyyy");
    QDate fin= QDate::fromString(ui->editfin->text(), "dd-MM-yyyy");

    QString statut= ui->editstatut->text();
    QString description= ui->editdescription->text();
    QString organisme= ui->editorganisme->text();
    QString certif= ui->editcertif->text();
    int prix= ui->editprix->text().toInt();

    Formations F(id,nom,debut,fin,statut,description,organisme,certif,prix);
    //Formations F;
     selectedDate = debut;

    bool test= F.ajouter();

    if(test)
    {
        ui->liste->setModel(f.afficher());
        // Appliquez le style à la date sélectionnée dans le calendrier
                majCalendrierAvecDateDebut(selectedDate);


        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        // Appliquez le style à la date sélectionnée dans le calendrier
                QDate currentDate = ui->calendrier->selectedDate();
                if (currentDate == selectedDate)
                {
                    QTextCharFormat format;
                    format.setBackground(Qt::yellow);
                    ui->calendrier->setDateTextFormat(selectedDate, format);
                }

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}



void gesformation::on_supprimer_clicked()
{
    Formations f;
    f.setid(ui->idsupp->text().toInt());


    // Récupérez la date associée à la formation que vous supprimez
        QSqlQuery query;
        query.prepare("SELECT debut FROM formations WHERE id = :id");
        query.bindValue(":id", f.getid());
        if (query.exec() && query.next())
        {
            QDate dateSupprimee = query.value(0).toDate();

            // Retirez la couleur associée à cette date dans le calendrier
            QTextCharFormat format;
            ui->calendrier->setDateTextFormat(dateSupprimee, format);

            // Retirez également l'information de la date colorée de votre structure de données
            datesColorees.remove(dateSupprimee);
            sauvegarderDatesColorees();  // Sauvegardez les modifications dans le fichier
        }









    bool test=f.supprimer(f.getid());
    if(test)
    {
        ui->liste->setModel(f.afficher());

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("supp effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("supp non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}




void gesformation::on_modifier_clicked() {

    Formations f;
    int id = ui->editidmodif->text().toInt();
    QString attribut = ui->editnomattribut->text();
    QString nouvelleValeur = ui->editnouvval->text();

    // Récupérez la date avant la modification
        QSqlQuery query;
        query.prepare("SELECT debut FROM formations WHERE id = :id");
        query.bindValue(":id", id);
        if (query.exec() && query.next())
        {
            QDate ancienneDate = query.value(0).toDate();
            supprimerDateCalendrier(ancienneDate);
        }

    bool test = f.modifier(id, attribut, nouvelleValeur);

    if (test) {
        ui->liste->setModel(f.afficher());

        // Appliquez le style à la nouvelle date dans le calendrier
                majCalendrierAvecDateDebut(QDate::fromString(nouvelleValeur, "dd-MM-yyyy"));


        QMessageBox::information(nullptr, QObject::tr("Ok"),
            QObject::tr("Modification effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
            QObject::tr("Modification non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}




void gesformation::on_rechercher_clicked()
{
        Formations f;
        QString n=ui->nomrech->text();
        bool test = f.rechercher(n);

        if (test) {
            //ui->listeR->setModel(model);

           /* QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("Recherche effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                QObject::tr("Recherche non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    */
            QSqlQueryModel * model= new QSqlQueryModel;

            //model->setQuery("SELECT id,nom from formations WHERE nom = :n");
            model->setQuery("SELECT id, nom FROM formations WHERE nom = '" + n + "'");

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            ui->listeR->setModel(model);
            ui->listeR->resizeColumnsToContents();
        }else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Recherche non effectuée."), QMessageBox::Cancel);
        }
    }


void gesformation::on_trier_clicked()
{
    Formations f;
    ui->liste->setModel(f.trier());
}

void gesformation::on_exporter_clicked()
{
        Formations f;

        QString nomFichierPDF = "liste_formations.pdf"; // Spécifiez le nom du fichier PDF

        f.exportToPDF(nomFichierPDF);

        // Vérifiez si le fichier PDF a été créé avec succès
        QFile fichierPDF(nomFichierPDF);
        if (fichierPDF.exists()) {
            // Le fichier PDF a été créé avec succès, vous pouvez effectuer des actions supplémentaires si nécessaire.
            // Par exemple, afficher un message de confirmation à l'utilisateur.
            QMessageBox::information(this, "Exportation PDF", "Le fichier PDF a été créé avec succès.");
        } else {
            // Le fichier PDF n'a pas été créé, affichez un message d'erreur.
            QMessageBox::critical(this, "Exportation PDF", "Erreur lors de la création du fichier PDF.");
        }
}



void gesformation::chargerDatesColorees()
{
    QFile file("dates_colorees.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if (parts.size() == 3)
            {
                QDate date = QDate::fromString(parts[0], "yyyy-MM-dd");
                QColor color(parts[1].toInt(), parts[2].toInt(), 0); // Conversion des parties de couleur en QColor
                datesColorees[date] = color;
            }
        }
        file.close();
    }
}






void gesformation::sauvegarderDatesColorees()
{
    QFile file("dates_colorees.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (auto it = datesColorees.begin(); it != datesColorees.end(); ++it)
        {
            QDate date = it.key();
            QColor color = it.value();
            out << date.toString("yyyy-MM-dd") << ":" << color.red() << ":" << color.green() << "\n";
        }
        file.close();
    }
}










// Ajoutez cette fonction à votre classe MainWindow (mainwindow.cpp)
void gesformation::majCalendrierAvecDateDebut(const QDate& date)
{
    QTextCharFormat format;
    format.setBackground(Qt::yellow);
    ui->calendrier->setDateTextFormat(date, format);

    // Sauvegarde la date colorée
        datesColorees[date] = Qt::yellow;
        sauvegarderDatesColorees();
}


void gesformation::chargerCalendrierAvecDatesColorees()
{
    for (auto it = datesColorees.begin(); it != datesColorees.end(); ++it)
    {
        QDate date = it.key();
        QColor color = it.value();
        QTextCharFormat format;
        format.setBackground(color);
        ui->calendrier->setDateTextFormat(date, format);
    }
}










// Ajoutez cette fonction dans votre classe MainWindow (mainwindow.cpp)
void gesformation::mettreAJourTableView(const QDate& date)
{
    QSqlQueryModel* model = new QSqlQueryModel;

    // Effectuez votre requête SQL pour récupérer les informations associées à la date
    QSqlQuery query;
    query.prepare("SELECT nom, debut, fin FROM formations WHERE debut = :date");
    query.bindValue(":date", date);
    if (query.exec() && query.next())
    {
        // Si la requête réussit, mettez à jour le modèle avec les informations de la base de données
        model->setQuery(query);
    }
    else
    {
        // Gérez l'erreur si la requête échoue
        qDebug() << "Erreur lors de la récupération des informations de la base de données.";
    }

    // Appliquez le modèle au QTableView
    ui->listeC->setModel(model);
    ui->listeC->resizeColumnsToContents();
}




void gesformation::supprimerDateCalendrier(const QDate& date)
{
    QTextCharFormat format;
    ui->calendrier->setDateTextFormat(date, format);
    datesColorees.remove(date);
    sauvegarderDatesColorees();  // Sauvegardez les modifications dans le fichier
}




void gesformation::handleOkButton() {
    // Code à exécuter lorsque le bouton "OK" est cliqué
    // Par exemple : récupérer la date et l'heure sélectionnées
    QDateTime selectedDateTime = dateTimeEditConfig->dateTime();

    // Calculer la date et l'heure une heure avant
    QDateTime notificationDateTime = selectedDateTime.addSecs(-3600);

    // Calculer la durée avant la notification
    qint64 timeToNotification = QDateTime::currentDateTime().secsTo(notificationDateTime);

    // Configurer un temporisateur pour déclencher la notification
    QTimer *notificationTimer = new QTimer(this);
    connect(notificationTimer, &QTimer::timeout, [=]() {
        // Code pour afficher la notification en utilisant QSystemTrayIcon
        QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
        QIcon icon("C:\\Users\\nadaa\\OneDrive\\Bureau\\icone");  // Remplacez par le chemin de votre icône
        trayIcon->setIcon(icon);
        trayIcon->show();
        trayIcon->showMessage("Notification", "Il est temps !", QSystemTrayIcon::Information, 5000);  // Afficher la notification pendant 5 secondes

        notificationTimer->deleteLater(); // Supprimer le temporisateur après utilisation
    });


    notificationTimer->start(timeToNotification * 1000); // Convertir en millisecondes
    // Fermer la boîte de dialogue après la configuration
        configDialog->close();


    // Fermer la boîte de dialogue
    configDialog->accept();
}

void gesformation::handleCancelButton() {
    // Code à exécuter lorsque le bouton "Annuler" est cliqué
    // Par exemple : annuler toute action en cours
    // Fermer la boîte de dialogue
    configDialog->reject();
}





void gesformation::on_pb_stats_clicked()
{
    QSqlQuery query;
    QMap<QString, qreal> pricesCount;

    query.prepare("SELECT prix FROM formations");
    if (query.exec()) {
        while (query.next()) {
            qreal price = query.value(0).toReal();

            // Déterminez la plage de prix pour chaque prix récupéré
            QString priceRange;
            if (price < 100) {
                priceRange = "0 - 100";
            } else if (price >= 100 && price < 200) {
                priceRange = "100 - 200";
            } else if (price >= 200 && price < 300) {
                priceRange = "200 - 300";
            } else {
                priceRange = "Above 300";
            }

            // Incrémentez le nombre de prix pour la plage de prix correspondante
            pricesCount[priceRange]++;
        }
    }

    // Créez le diagramme à barres pour représenter la distribution des prix
    QChart *barChart = new QChart();
    QBarSeries *barSeries = new QBarSeries();

    // Parcourez le QMap pour créer un QBarSet pour chaque plage de prix
    for (auto it = pricesCount.begin(); it != pricesCount.end(); ++it) {
        QBarSet *barSet = new QBarSet(it.key());
        *barSet << it.value();
        barSeries->append(barSet);
    }

    // Ajoutez le QBarSeries au QChart
    barChart->addSeries(barSeries);

    // Configurez la vue du diagramme à barres
    QChartView *barChartView = new QChartView(barChart, static_cast<QWidget*>(this));
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->setMinimumSize(800, 600);

    // Configurez la mise en page principale de la fenêtre
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(barChartView);

    // Créez une nouvelle boîte de dialogue pour le diagramme et définissez sa mise en page
    QDialog *chartDialog = new QDialog(this);
    chartDialog->setLayout(layout);
    chartDialog->setWindowTitle("Price Statistics");

    // Créez un bouton pour fermer la boîte de dialogue
    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, chartDialog, &QDialog::close);

    // Ajoutez le bouton à la disposition de la boîte de dialogue
    layout->addWidget(closeButton);

    // Affichez la boîte de dialogue
    chartDialog->exec();
}

/*
void gesformation::on_pushButton_clicked()
{
    Arduino arduino;
    QString idToSend = ui->idarduino->text(); // Récupérer le texte de QLineEdit
        // Envoyer l'ID à Arduino via la communication série
// Connexion à Arduino
    int connectionResult = arduino.connect_arduino();
    if (connectionResult == 0) {
        qDebug() << "Connected to Arduino!";

        // Envoyer l'ID à Arduino via la communication série
        arduino.write_to_arduino(idToSend.toLatin1());
    } else if (connectionResult == 1) {
        qDebug() << "Error opening serial port!";
        // Affichez un message à l'utilisateur indiquant qu'il y a eu une erreur lors de l'ouverture du port série
        QMessageBox::critical(this, "Error", "Failed to open serial port to Arduino!");
    } else {
        qDebug() << "Arduino not found on specified serial port!";
        // Affichez un message à l'utilisateur indiquant qu'Arduino n'a pas été détecté sur le port série spécifié
        QMessageBox::warning(this, "Warning", "Arduino not found on specified serial port!");
    }
}*/







/*
void gesformation::on_pushButton_clicked() {
    // Récupérer l'ID à partir de l'interface utilisateur
    QString idToSend = ui->idarduino->text();

    // Effectuer la recherche de l'ID dans la base de données en utilisant la fonction existante
    Formations formations;
    bool idExists = formations.rechercher(idToSend);

    // Si l'ID existe dans la base de données
    if (idExists) {
        // Envoyer un signal à Arduino pour jouer le son
        arduino.playSound();
    } else {
        // L'ID n'existe pas dans la base de données, vous pouvez afficher un message ou prendre d'autres mesures
        QMessageBox::warning(this, "ID not found", "The entered ID does not exist in the database.");
    }
}
*/



/*
void gesformation::on_pushButton_clicked() {
    // Récupérer l'ID à partir de l'interface utilisateur
    QString idToSend = ui->idarduino->text();

    // Effectuer la recherche de l'ID dans la base de données en utilisant la fonction existante
    Formations formations;
    bool idExists = formations.rechercher(idToSend);

    if (idExists) {
        qDebug() << "trouveee";

        Arduino arduino;  // Instanciation de la classe Arduino
        int connectionStatus = arduino.connect_arduino();  // Connexion à l'Arduino

        if (connectionStatus == 0) {  // Vérification de la connexion réussie
            // Envoyer la commande "playsound" à l'Arduino en utilisant la fonction write_to_arduino
            QByteArray commandToSend = "playsound\n";
            int writeStatus = arduino.write_to_arduino(commandToSend);

            if (writeStatus == 0) {
                qDebug() << "Command sent successfully!";
                arduino.close_arduino();  // Fermeture de la connexion après l'envoi de la commande
            } else {
                qDebug() << "Failed to send command!";
            }
        } else {
            qDebug() << "Failed to connect to Arduino.";
        }
    } else {
        // L'ID n'existe pas dans la base de données, afficher un message d'avertissement
        QMessageBox::warning(this, "ID not found", "The entered ID does not exist in the database.");
    }
}*/




void gesformation::on_pushButton_clicked() {

    QString idToSend = ui->idarduino->text();

    Formations formations;
    bool idExists = formations.rechercher(idToSend);

    if (idExists) {
        qDebug() << "trouveee";

        Arduino arduino;  // Instanciation de la classe Arduino
        int connectionStatus = arduino.connect_arduino();  // Connexion à l'Arduino

        if (connectionStatus == 0) {  // Vérification de la connexion réussie
            // Envoyer 1 ou 0 à l'Arduino en fonction de l'existence de l'ID
            QByteArray dataToSend = idExists ? "1\n" : "0\n";
            int writeStatus = arduino.write_to_arduino(dataToSend);

            if (writeStatus == 0) {
                qDebug() << "Data sent successfully!";
                //arduino.close_arduino();  // Fermeture de la connexion après l'envoi des données
            } else {
                qDebug() << "Failed to send data!";
            }
        } else {
            qDebug() << "Failed to connect to Arduino.";
        }
    } else {
        // L'ID n'existe pas dans la base de données, afficher un message d'avertissement
        QMessageBox::warning(this, "ID not found", "The entered ID does not exist in the database.");
    }

}








/*
void gesformation::on_pushButton_clicked()
{
    // Récupérer l'ID à partir de l'interface utilisateur
    QString idToSend = ui->idarduino->text();

    // Effectuer la recherche de l'ID dans la base de données en utilisant la fonction existante
    Formations formations;
    //bool idExists = formations.rechercher(idToSend);
    // Créez une instance de la classe Ventes

    if (formations.rechercher(idToSend)) {
        QByteArray dataToSend;
        dataToSend.append(idToSend);
             arduino.write_to_arduino(dataToSend);

        } else {

            arduino.write_to_arduino("0\n");

        }

}

*/
