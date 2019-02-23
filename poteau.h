#ifndef POTEAU_H
#define POTEAU_H
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
class Poteau;
}

class Poteau : public QMainWindow
{
    Q_OBJECT

public:
    explicit Poteau(QWidget *parent = 0);
    ~Poteau();
    Poteau();
    Poteau(int,QString,QString,QString,QString,QString);
    bool ajouter_Poteau();
    QSqlQuery existPoteau(int);
    bool modifier_Poteau(int);
    bool deletePoteau(int);
    QSqlQueryModel*  afficher();
    bool existnomcapteur(QString  );
    bool  existnumero(int );
    QString verifetat(int);
    QSqlQueryModel* addtocombo();
    QSqlQueryModel* status(int num);
    void addHistory(int,QString,QDate);
    QSqlQueryModel* affichehist(int , int all);
    int  get_niveau(int num);
    QChartView * Stats(int,int,int);


private slots:
    void on_actionAjouter_triggered();

    void on_actionModifier_triggered();

    void on_actionSupprimer_triggered();

    void on_actionAfficher_triggered();

    void on_actionHistorique_triggered();

    void on_actionEtat_triggered();

    void on_actionQuitter_triggered();

    void on_ajouterpo_clicked();

    void on_annulerajpo_clicked();

    void on_rechmopo_clicked();

    void on_annulermopo_clicked();

    void on_enregistrermopo_clicked();

    void on_rechsupppo_clicked();

    void on_annulersupppo_clicked();

    void on_supprimerpo_clicked();

    void on_verifieretatpo_clicked();

    void on_verifiercandelabre_clicked();

    void on_verfier_stat_clicked();

    void on_actionStatistiques_triggered();

private:
    Ui::Poteau *ui;
    QString Nom,Lieu,Commentaire,NomCapteur,etat;
        int Numero;
        int NiveauLum;
        QDate date_po;
};

#endif // POTEAU_H
