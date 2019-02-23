#ifndef CANDELABRE_H
#define CANDELABRE_H

#include <QMainWindow>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QComboBox>
#include<QDate>
#include<QGridLayout>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include<QSerialPort>


QT_CHARTS_USE_NAMESPACE
namespace Ui {
class Candelabre;
}

class Candelabre : public QMainWindow
{
    Q_OBJECT

public:
    explicit Candelabre(QWidget *parent = 0);
    ~Candelabre();
    Candelabre();
    Candelabre(int,QString,QString,QString,QString,int,QString);
    bool ajouter_Candelabre();
    QSqlQuery existCandelabre(int);
    bool modifier_Candelabre(int);
    bool deleteCandelabre(int);
    QSqlQueryModel*  afficher();
    bool existnomcapteur(QString  );
    bool  existnumero(int );
    QString verifetat(int);
    QSqlQueryModel* addtocombo();
    QSqlQueryModel* status(int num);
    void addHistory(int,QString,QDate);
    QSqlQueryModel* affichehist(int , int all);
    int  get_niveau(int num);
    bool changerniveau(int ,int );
    QChartView * Stats(int,int,int);

    void niveauarduino(QSerialPort *a,QString);



private slots:

    void on_actionEtat_triggered();

    void on_actionHistorique_triggered();

    void on_actionAjouter_triggered();

    void on_actionModifier_triggered();

    void on_actionSupprimer_triggered();

    void on_actionAfficher_triggered();

    void on_actionQuitter_triggered();

    void on_ajouterc_clicked();

    void on_annulerajc_clicked();

    void on_rechmoc_clicked();

    void on_annulermoc_clicked();

    void on_enregistrermoc_clicked();

    void on_rechsuppc_clicked();

    void on_annulersuppc_clicked();

    void on_supprimerc_clicked();

    void on_verifieretatc_clicked();

    void on_verifiercandelabre_clicked();

    void on_Changerniv_clicked();

    void on_verfier_stat_clicked();

    void on_actionStatistiques_triggered();

private:
    Ui::Candelabre *ui;
    QString Nom,Lieu,Commentaire,NomCapteur,etat;
        int Numero;
        int NiveauLum;
        QDate date_c;


};

#endif // CANDELABRE_H

