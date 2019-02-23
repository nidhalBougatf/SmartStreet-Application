#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QMainWindow>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDebug>
namespace Ui {
class Employee;
}

class Employee : public QMainWindow
{
    Q_OBJECT

public:
    explicit Employee(QWidget *parent = 0);
    ~Employee();

    Employee(QString,QString,QString,QString,QString,QString,QString);

    bool addEmployee();

    bool editEmployee(QString );

    QSqlQuery existEmployee(QString );

    bool verifEmployee(QString );


    bool deleteEmployee(QString );

    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherhistorique(QString ,int);
    QSqlQueryModel* addtocombo();




private slots:
    void on_actionAjouter_triggered();

    void on_actionModifier_triggered();

    void on_actionSupprimer_triggered();

    void on_actionAfficher_triggered();

    void on_actionQuitter_triggered();

    void on_Enregistrer_clicked();


    void on_Annuler_clicked();

    void on_RechercherModif_clicked();

    void on_Annuler_2_clicked();

    void on_Sauvegarder_clicked();

    void on_rechsupp_clicked();

    void on_Annuler_3_clicked();

    void on_Supprime_clicked();

    void on_actionAuto_Gen_triggered();

    void on_actionDelt_Gen_triggered();

    void on_actionHistorique_triggered();

    void on_verifier_clicked();

private:
    Ui::Employee *ui;
    QString pseudo;
    QString nom;
    QString prenom;
    QString mdp;
    QString CIN;
    QString fonction;
    QString type;
};

#endif // EMPLOYEE_H
