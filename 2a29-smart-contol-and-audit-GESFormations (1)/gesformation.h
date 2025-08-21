#ifndef GESFORMATION_H
#define GESFORMATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

#include <QMessageBox>
#include <formations.h>

#include "arduino.h"

#include <QTimer>
#include <QMessageBox>
#include <QDateTimeEdit>


#include <QSqlTableModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <serialcommunication.h>
QT_CHARTS_USE_NAMESPACE
namespace Ui { class gesformation; }
QT_END_NAMESPACE

class gesformation : public QMainWindow
{
    Q_OBJECT

public:
    gesformation(QWidget *parent = nullptr);
    ~gesformation();

private slots:
    void on_ajouter_clicked();

    //void on_ajouter_clicked(bool checked);

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_rechercher_clicked();

    void on_trier_clicked();

    void on_exporter_clicked();

    void majCalendrierAvecDateDebut(const QDate& date);
    void mettreAJourTableView(const QDate& date);


    void on_pushButtonConfig_clicked();


//public
    void handleOkButton();
    void handleCancelButton();



    void on_pb_stats_clicked();

    void on_pushButton_clicked();

private:
    Ui::gesformation *ui;
    Formations f;
        QDate selectedDate;
        void chargerDatesColorees();

        void sauvegarderDatesColorees();
        void chargerCalendrierAvecDatesColorees();

        QMap<QDate, QColor> datesColorees;
        //QTableView* listeC;
        void supprimerDateCalendrier(const QDate& date);


        QDialog *configDialog;
        QDateTimeEdit *dateTimeEditConfig;

        //SerialCommunication serialcommunication;
        Arduino arduino;
};








#endif // GESFORMATION_H











