#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QDebug>
 class SerialCommunication : public QObject //QSerialPort
{/*
Q_OBJECT
public:
    explicit SerialCommunication(QObject *parent = nullptr);
    void openSerialPort();
    void sendIDToArduino(QString employeeID);
    void rechercheDansBaseDeDonnees(QString employeeID);
    void sendCommandToArduino(const QString &command);
    QSerialPort* getSerial() const {
            return serial;
        }

signals:
    void dataReceived(); // Ajoutez un signal pour indiquer la réception de données

public slots:
  void readData();

private:
  QSerialPort *serial;
  // Déclaration de la variable message
      QString message;*/

 public:     //méthodes de la classe Arduino
     SerialCommunication();
     int connect_arduino(); // permet de connecter le PC à Arduino
     int close_arduino(); // permet de femer la connexion
     int write_to_arduino( QByteArray ); // envoyer des données vers arduino
     QByteArray read_from_arduino();  //recevoir des données de la carte Arduino
     QSerialPort* getserial();   // accesseur
     QString getarduino_port_name();
     //void setFlameHigh(bool high);

 private:
  //bool isFlameHigh;
 QSerialPort * serial; //Cet objet rassemble des informations (vitesse, bits de données, etc.)
 //et des fonctions (envoi, lecture de réception,…) sur ce qu’est une voie série pour Arduino.
 static const quint16 arduino_uno_vendor_id=9025;
 static const quint16 arduino_uno_producy_id=67;
 QString arduino_port_name;
 bool arduino_is_available;
 QByteArray data;  // contenant les données lues à partir d'Arduino

};

#endif // SERIALCOMMUNICATION_H





