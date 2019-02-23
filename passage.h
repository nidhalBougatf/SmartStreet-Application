#ifndef PASSAGE_H
#define PASSAGE_H

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
class Passage;
}

class Passage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Passage(QWidget *parent = 0);
    ~Passage();
    Passage();
    Passage(int,QString,QString,QString,QString,QString);

    bool ajouter_Passage();
    bool modifier_Passage(int);
    bool deletePassage(int);
    QSqlQuery existPassage(int);
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

private slots:

    void on_actionQuitter_triggered();

    void on_actionAjouter_triggered();

    void on_actionModifier_triggered();

    void on_actionSupprimer_triggered();

    void on_actionAfficher_triggered();

    void on_actionHistorique_triggered();

    void on_actionEtat_triggered();

    void on_ajouterpa_clicked();

    void on_annuleraj_clicked();

    void on_Rechercher_clicked();

    void on_annlermo_clicked();

    void on_enregistrer_clicked();

    void on_Rechercher_2_clicked();

    void on_annlersupp_clicked();

    void on_Supprimer_2_clicked();

    void on_verifieretatpa_clicked();

    void on_verifierhist_clicked();

    void on_actionStatistiques_triggered();

    void on_verfier_stat_clicked();

private:
    Ui::Passage *ui;
    QString Nom,Lieu,Commentaire,NomCapteur,etat;
        int Numero;
        QDate date_pa;
};

#endif // PASSAGE_H
