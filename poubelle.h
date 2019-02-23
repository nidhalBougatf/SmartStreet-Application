#ifndef POUBELLE_H
#define POUBELLE_H

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

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class Poubelle;
}

class Poubelle : public QMainWindow
{
    Q_OBJECT

public:
    explicit Poubelle(QWidget *parent = 0);
    ~Poubelle();
    Poubelle();
    Poubelle(int,QString,QString,QString,QString,QString);
    bool ajouter_Poubelle();
    QSqlQuery existPoubelle(int);
    bool modifier_Poubelle(int);
    bool deletePoubelle(int);
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

    void on_Ajouter_po_clicked();

    void on_annulerajpo_clicked();

    void on_Rechercher_clicked();

    void on_annulermod_clicked();

    void on_Enregistrer_clicked();

    void on_Recherchersupp_clicked();

    void on_annulersupp_clicked();

    void on_supprimer_clicked();

    void on_verifierhistpo_clicked();

    void on_Verifierpo_clicked();

    void on_actionStatistiques_triggered();

    void on_verfier_stat_clicked();

private:
    Ui::Poubelle *ui;
    QString Nom,Lieu,Commentaire,NomCapteur,etat;
    int Numero;
    QDate date_po;
};

#endif // POUBELLE_H
