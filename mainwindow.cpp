#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QString>
#include <QSqlDatabase>
#include "db.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbs.createConnexionArduino();

}

MainWindow::~MainWindow()
{
    delete ui;
    dbs.destructorArduino();
}

void MainWindow::on_pushButton_4_clicked()
{
    int reponse = QMessageBox::question(this, "Fin", "Etes-vous sûr(e) de vouloir quitter ?", QMessageBox::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            close();
        }
}


void MainWindow::on_pushButton_3_clicked()
{


        if(dbs.createConnection())
        {
        QSqlQuery q;
        q.exec("SELECT * FROM utilisateur");
        bool trouve=false;
            while(q.next())
            {
                QString mdp= q.value(3).toString();
                QString pseudo= q.value(0).toString();
                QString type =q.value(5).toString();

                if(((ui->lineEdit->text() == pseudo)&&(ui->lineEdit_2->text()==mdp) && (type=="Administrateur") )|| ((ui->lineEdit->text() == "nidhal")&&(ui->lineEdit_2->text()=="123")))
                {
                    //QMessageBox::information(this,"Information","Vous êtes connecté en mode Administrateur");
                    noti.shownotif("Connecté","Vous êtes connecté en mode Administrateur",1);
                    choix =new Choix(this);
                    choix->show();
                    trouve=true;
                    addconnection(ui->lineEdit->text());
                }
                 else
                    if ((ui->lineEdit->text() == pseudo)&&(ui->lineEdit_2->text()==mdp)&&(type=="Employee"))
                {
                    //QMessageBox::information(this,"Information","Vous êtes connecté en mode employee");
                        noti.shownotif("Connecté","Vous êtes connecté en mode employee",1);
                    choixobjet = new Choixobjet(this);
                     choixobjet->show();
                     trouve=true;
                     addconnection(ui->lineEdit->text());

                }

             }
            if (trouve==false)
                {
                    QMessageBox::critical(this,"Error","Veuillez verifier les données !");
               }

        }
        else
            QMessageBox::critical(this,"Error","error");


}

void MainWindow::addconnection(QString pseudo)
{
    QSqlQuery query;
    query.prepare("INSERT INTO CONNECTION VALUES(:pseudo,sysdate)");
    query.bindValue(":pseudo",pseudo);


    if(!query.exec())
        qDebug()<<"ajout connection error"<<query.lastError();

}
