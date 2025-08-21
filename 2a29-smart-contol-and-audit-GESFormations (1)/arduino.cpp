#include "arduino.h"
#include <QMessageBox>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QDebug>
#include "serialcommunication.h"
#include <QDebug>
#include <formations.h>
#include <QMediaPlayer>
#include <QUrl>
#include <QTimer>
#include <QMessageBox>
Arduino::Arduino()
{

        data="";
        arduino_port_name="COM5";
        arduino_is_available=false;
        serial=new QSerialPort;
        //isFlameHigh = false; // Ajout de cette ligne
}



QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino() {
    // Recherche du port sur lequel la carte Arduino identifiée par arduino_uno_vendor_id est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }

    qDebug() << "arduino_port_name is :" << arduino_port_name;

    if (arduino_is_available) {
        // Configuration de la communication (débit...)
        serial->setPortName(arduino_port_name);

        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600); // Débit : 9600 bits/s
            serial->setDataBits(QSerialPort::Data8); // Longueur des données : 8 bits,
            serial->setParity(QSerialPort::NoParity); // 1 bit de parité optionnel
            serial->setStopBits(QSerialPort::OneStop); // Nombre de bits de stop : 1
            serial->setFlowControl(QSerialPort::NoFlowControl);

            qDebug() << "Connected to Arduino!";
            return 0; // Connexion établie avec succès
        }
        return 1; // Erreur lors de l'ouverture du port série
    }
    return -1; // Aucun Arduino détecté sur le port série spécifié
}


int Arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


QByteArray Arduino::read_from_arduino() {
    if(serial->isReadable()) {
         data = serial->readAll(); // Récupérer les données reçues
         return data;
    } else {
        return QByteArray(); // Retourner un QByteArray vide ou une valeur par défaut
    }
}



int Arduino::write_to_arduino(QByteArray d) {
    if(serial->isWritable()) {
        serial->write(d);  // Envoyer des données vers Arduino
        return 0; // Indiquer le succès de l'envoi des données


    } else {
        qDebug() << "Couldn't write to serial!";
        return -1; // Indiquer l'échec de l'envoi des données
    }
}

