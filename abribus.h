#ifndef ABRIBUS_H
#define ABRIBUS_H

#include <QMainWindow>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QComboBox>
#include<QDate>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Abribus;
}

class Abribus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Abribus(QWidget *parent = 0);
    ~Abribus();
    Abribus();
    Abribus(int,QString,QString,QString,QString,QString);
    bool ajouter_Abribus();
    QSqlQuery existAbribus(int);
    bool modifier_Abribus(int);
    bool deleteAbribus(int);
    QSqlQueryModel*  afficher();
    bool existnomcapteur(QString  );
    bool  existnumero(int );
    QString verifetat(int);
    QSqlQueryModel* addtocombo();
    QSqlQueryModel* status(int num);
    void addHistory(int,QString,QDate);
    QSqlQueryModel* affichehist(int , int all);
    QChartView * Stats(int,int,int);





private slots:
    void on_actionAjouter_triggered();

    void on_actionModifier_triggered();

    void on_actionSupprimer_triggered();

    void on_actionAfficher_triggered();

    void on_actionHistorique_triggered();

    void on_actionEtat_triggered();

    void on_actionQuitter_triggered();

    void on_Ajouter_2_clicked();

    void on_annuleraj_clicked();

    void on_Rechercher_clicked();

    void on_annulermod_clicked();

    void on_Enregistrer_clicked();

    void on_Recherchersupp_clicked();

    void on_annulersupp_clicked();

    void on_supprimer_clicked();

    void on_Verifier_clicked();

    void on_verifierhist_clicked();

    void on_actionStatistiques_triggered();

    void on_verfier_stat_clicked();

    void on_lieu_clicked();

private:
    Ui::Abribus *ui;
    QString Nom,Lieu,Commentaire,NomCapteur,etat;
    int Numero;
    QDate date_a;
};

#endif // ABRIBUS_H



