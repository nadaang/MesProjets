#include "serialcommunication.h"
#include <QDebug>
#include <formations.h>
#include <QMediaPlayer>
#include <QUrl>
#include <QTimer>
#include <QMessageBox>


/*
SerialCommunication::SerialCommunication(QObject *parent) : QObject(parent)
{

    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &SerialCommunication::readData);
    openSerialPort();
}


void SerialCommunication::openSerialPort() {

    QString portname = "COM4"; // Set the port name here

  const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
  for (const QSerialPortInfo &info : serialPortInfos) {
    if (info.description().contains("Arduino")) {
      serial->setPort(info);
      serial->setBaudRate(QSerialPort::Baud9600);
      if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to Arduino!";
      } else {
        qDebug() << "Serial Port error: " << serial->errorString();
      }
      break;
    }
  }
}



void SerialCommunication::sendIDToArduino(QString employeeID) {
    if(serial->isOpen() && serial->isWritable()) {
        serial->write(employeeID.toLatin1()); // Envoi de l'ID à Arduino via le port série
    } else {
        qDebug() << "Serial Port is not open or not writable";
    }
}





void SerialCommunication::readData() {
    QByteArray data = serial->readAll();
    QString employeeID = QString::fromLatin1(data).trimmed(); // Supprimer les espaces inutiles

    if (!employeeID.isEmpty()) {
        rechercheDansBaseDeDonnees(employeeID);
    }
}


void SerialCommunication::rechercheDansBaseDeDonnees(QString employeeID) {
    Formations formations;
    bool resultatRecherche = formations.rechercher(employeeID);

    if (resultatRecherche) {
        sendCommandToArduino("PLAY_MELODY"); // Envoyer une commande à Arduino pour déclencher la tonalité
    } else {
        // Gérer le cas où la recherche n'a pas abouti
    }
}








void SerialCommunication::sendCommandToArduino(const QString &command) {
    if (serial->isOpen() && serial->isWritable()) {
        serial->write(command.toLatin1()); // Envoyer la commande à Arduino
    } else {
        qDebug() << "Serial Port is not open or not writable";
    }
}


*/













/*
void SerialCommunication::readData() {
  QByteArray data = serial->readAll(); // Lecture des données reçues
  QString employeeID = QString::fromLatin1(data); // Conversion en QString
  qDebug() << "Received Employee ID: " << employeeID;
  // Simuler l'envoi de l'ID reçu pour une recherche dans la base de données et le déclenchement du son


  // Vérification de la commande reçue depuis Arduino
      if (message == "RECHERCHE_BD") {
          // Appel de votre fonction de recherche dans la base de données
          // (par exemple, rechercheDansBaseDeDonnees() qui effectue la recherche)
          // rechercheDansBaseDeDonnees();
          // Suite à la recherche, vous pouvez déclencher le module MP3 si nécessaire
          rechercheDansBaseDeDonnees();
      }

}*/




/*
void SerialCommunication::rechercheDansBaseDeDonnees() {

    Formations formations; // Créez une instance de votre classe qui contient la fonction rechercher()
        bool resultatRecherche = formations.rechercher("votre_texte_a_rechercher"); // Remplacez par le texte à rechercher

        // Suite à la recherche, vous pouvez déclencher le module MP3 si nécessaire
        if (resultatRecherche) {
            // Effectuer des actions supplémentaires si la recherche est réussie
            // Par exemple, pour déclencher la lecture d'un fichier audio (un son)
                    QMediaPlayer* player = new QMediaPlayer;
                    player->setMedia(QUrl::fromLocalFile("chemin_vers_votre_fichier_audio.mp3"));
                    player->setVolume(50); // Réglez le volume audio (0 - 100, 0 étant sans son, 100 étant le maximum)

                    // Commencez la lecture du fichier audio
                    player->play();
                    // Création d'un QTimer pour arrêter la lecture après 5 secondes
                    QTimer::singleShot(5000, [=]() {
                        // Arrêter la lecture après le délai spécifié (5000 ms = 5 secondes)
                        player->stop();
                        delete player; // N'oubliez pas de supprimer l'objet QMediaPlayer pour éviter les fuites de mémoire
                    });
        } else {
            // Gérer le cas où la recherche n'a pas abouti
        }
    }


*/




