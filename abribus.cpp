#include "abribus.h"
#include "ui_abribus.h"
#include<QSqlQuery>
#include<QDebug>
#include<QMessageBox>
#include "db.h"
#include<QtGui>
#include<mainwindow.h>
#include<QGridLayout>

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtQuick/QQuickView>

Abribus::Abribus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Abribus)
{
    ui->setupUi(this);
    on_actionAfficher_triggered();
}

Abribus::~Abribus()
{
    delete ui;
}



void Abribus::on_actionAjouter_triggered()
{
    ui->Ajouter->setVisible(true);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->comboBox_5->setStyleSheet( "QListView { color: white; }");

}

void Abribus::on_actionModifier_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(true);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->Numerorech->setModel(this->addtocombo());
    ui->Numerorech->setStyleSheet( "QListView { color: white; }");
    ui->etatmo->setStyleSheet( "QListView { color: white; }");

}

void Abribus::on_actionSupprimer_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(true);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->Numerorechsupp->setModel(this->addtocombo());
    ui->Numerosupp->setReadOnly(true);
    ui->Nomsupp->setReadOnly(true);
    ui->Lieusupp->setReadOnly(true);
    ui->Commentairesupp->setReadOnly(true);
    ui->NomCapteursupp->setReadOnly(true);
    ui->etatsupp->setDisabled(true);
    ui->Numerorechsupp->setStyleSheet( "QListView { color: white; }");


}

void Abribus::on_actionAfficher_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(true);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->tableView_afficher->setModel(this->afficher());
}

void Abribus::on_actionHistorique_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(true);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->Numerorechhist->setModel(this->addtocombo());
    ui->tableView_hist->setModel(affichehist(0,1));
    ui->Numerorechhist->setStyleSheet( "QListView { color: white; }");
}

void Abribus::on_actionEtat_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(true);
    ui->Statistiques->setVisible(false);
    ui->Numerorechetat->setModel(this->addtocombo());
    ui->Numerorechetat->setStyleSheet( "QListView { color: white; }");

}

void Abribus::on_actionStatistiques_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(true);
    ui->day->setStyleSheet( "QListView { color: white; }");
    ui->month->setStyleSheet( "QListView { color: white; }");



}

void Abribus::on_actionQuitter_triggered()
{
    close();
}

Abribus ::Abribus()
{
    Numero=0;Nom="";Lieu="";Commentaire="";NomCapteur="";etat="";
}


Abribus ::Abribus(int Numero, QString Nom, QString Lieu, QString Commentaire, QString NomCapteur,QString etat)
{
    this->Numero=Numero;
     this->Nom=Nom;
     this->Lieu=Lieu;
     this->Commentaire=Commentaire;
     this->NomCapteur=NomCapteur;
     this->etat=etat;
}



bool Abribus :: existnumero(int num )
{
    QSqlQuery query;
    query.prepare("SELECT numero FROM abribuss WHERE numero=:num");
    query.bindValue(":num", num);
    if(!query.exec())
    {
       qDebug() << "verfication numero   error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}

bool Abribus :: existnomcapteur(QString nom )
{
    QSqlQuery query;
    query.prepare("SELECT nom_capteur FROM abribuss WHERE nom_capteur=:nom");
    query.bindValue(":nom", nom);
    if(!query.exec())
    {
       qDebug() << "verfication nom cpateur   error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}

bool Abribus :: ajouter_Abribus()
{
    bool success=false;
    QSqlQuery query;
        query.prepare("INSERT INTO ABRIBUSS (NUMERO,NOM,LIEU,COMMENTAIRE,ETAT,NOM_CAPTEUR,date_ajout) VALUES (:Numero,:Nom,:Lieu,:Commentaire,:etat,:NomCapteur,sysdate)");
        query.bindValue(":Numero",Numero);
        query.bindValue(":Nom",Nom);
        query.bindValue(":Lieu",Lieu);
        query.bindValue(":Commentaire",Commentaire);
        query.bindValue(":etat",etat);
        int alea;

        do
        {
            alea=rand()%100+1;
            QString num = QString::number (alea);
            NomCapteur ="capteur"+num;
        }while(existnomcapteur(this->NomCapteur));

        query.bindValue(":NomCapteur",NomCapteur);
        if(query.exec())
        {
            success=true;
            qDebug()<<"Ajoutée";
        }

        else
            qDebug()<<"Ajout errone"<<query.lastError();;
        return success;
}



QSqlQuery Abribus :: existAbribus(int num)
{
    QSqlQuery query;
    query.prepare("SELECT numero,nom,lieu,commentaire,etat,nom_capteur FROM ABRIBUSS WHERE NUMERO=:numero");
    query.bindValue(":numero", num);
    if(!query.exec())
    {
       qDebug() << "Recherche  error:  "<< query.lastError();
    }
    return query;
}


QSqlQueryModel *Abribus::addtocombo()
{

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("Select Numero from Abribuss");
    return model;

}


bool Abribus :: modifier_Abribus(int Num)
{

QSqlQuery querydelete;
querydelete.prepare("DELETE FROM Abribuss WHERE Numero=:Numero");
querydelete.bindValue(":Numero", Num);
if(!querydelete.exec())
{
        qDebug() << "Modification(supp) abribus  error:  "<< querydelete.lastError();
        return false;
}
querydelete.finish();
     QSqlQuery query;
     query.prepare("INSERT INTO abribuss (NUMERO,NOM,LIEU,COMMENTAIRE,ETAT,NOM_CAPTEUR,date_ajout) VALUES (:Numero, :Nom, :Lieu,:Commentaire,:etat,:NomCapteur,:date)");
     query.bindValue(":Numero",Numero);
     query.bindValue(":Nom",Nom);
     query.bindValue(":Lieu",Lieu);
     query.bindValue(":Commentaire",Commentaire);
     query.bindValue(":NomCapteur",NomCapteur);
     query.bindValue(":etat",etat);
     query.bindValue(":date",QDate::currentDate());
 if(!query.exec())
 {
         qDebug() << "Modification abribus  error:  "<< query.lastError();
         return false;
 }

 return true;

}



bool Abribus :: deleteAbribus(int Num)
{
    QSqlQuery querydelete;
    querydelete.prepare("DELETE FROM Abribuss WHERE Numero=:Numero");
    querydelete.bindValue(":Numero",Num);
    if(!querydelete.exec())
    {
            qDebug() << "Suppression abribus error:  "<< querydelete.lastError();
            return false;
    }
    return true;
}



QSqlQueryModel*Abribus::status(int num)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    query.prepare("Select nom,lieu,etat from Abribuss where numero=:num");
    query.bindValue(":num",num);
    query.exec();
    model->setQuery(query);
    QString namecolumn0="Nom";
    QString namecolumn1="Lieu";
    QString namecolumn2="Etat";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    model->setHeaderData(2, Qt::Horizontal,namecolumn2);
    return model;
}







void Abribus::on_Ajouter_2_clicked()
{
    Numero=ui->spinBox->value();
    Nom=ui->lineEdit_2->text();
    Lieu=ui->lineEdit_3->text();
    Commentaire=ui->textEdit->toPlainText();
    etat=ui->comboBox_5->currentText();

    QString resultat1="L'abribus "+Nom+" a été ajouté !";
    QString resultat2="L'abribus "+Nom+" n'a pas été ajouté !";

    if(existnumero(Numero))
        QMessageBox::information(NULL,"Numero","Numero existe deja !");
    else
    {
        if (this->ajouter_Abribus())
            {
            QMessageBox::information(NULL,"Ajout",resultat1);
            this->on_annuleraj_clicked();
            addHistory(Numero,"Ajout",QDate::currentDate());
           }
           else
            QMessageBox::information(NULL,"Ajout",resultat2);
    }
}


void Abribus::on_annuleraj_clicked()
{
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->textEdit->clear();
    ui->spinBox->cleanText();


}

void Abribus::on_Rechercher_clicked()
{

  int   Num=ui->Numerorech->currentText().toInt();
   QSqlQuery resultat=existAbribus(Num);

   if(resultat.first())
   {
       ui->Numeromo->setText(resultat.value(0).toString());
       ui->Nommo->setText(resultat.value(1).toString());
       ui->Lieumo->setText(resultat.value(2).toString());
       ui->Commentairemo->setText(resultat.value(3).toString());
       ui->etatmo->setCurrentText(resultat.value(4).toString());
       ui->NomCapteurmo->setText(resultat.value(5).toString());

   }
   else
    {
       QMessageBox::information(NULL,"Recherche","Abribus introuvable");
       on_annulermod_clicked();
    }

}

void Abribus::on_annulermod_clicked()
{
    ui->Numeromo->clear();
    ui->Nommo->clear();
    ui->Lieumo->clear();
    ui->Commentairemo->clear();
    ui->NomCapteurmo->clear();
    ui->etatmo->clear();
}

void Abribus::on_Enregistrer_clicked()
{
    Numero = ui->Numeromo->text().toInt();
    Nom = ui->Nommo->text();
    Lieu = ui->Lieumo->text();
    Commentaire=ui->Commentairemo->toPlainText();
    NomCapteur=ui->NomCapteurmo->text();
    etat=ui->etatmo->currentText();
    QString Nu=QString::number(Numero);
    QString resultat1="Les données de ' " +Nu+" ' "+" ont été modifié !";
    QString resultat2="Les données de ' "+Nu+" ' "+" n'ont pas été modififé !";

    if( (!existnumero(Numero)) || (Numero==ui->Numerorech->currentText().toInt()))
    {
        if(modifier_Abribus(ui->Numerorech->currentText().toInt()))
           {
              QMessageBox::information(NULL,"Modification",resultat1);
              on_annulermod_clicked();
              if(ui->Numerorech->currentText().toInt()!=Numero)
              {

                  addHistory(ui->Numerorech->currentText().toInt(),"Supression",QDate::currentDate());
                  addHistory(Numero,"Ajout",QDate::currentDate());

              }
              else
                  addHistory(ui->Numerorech->currentText().toInt(),"Modification",QDate::currentDate());

           }
        else
            QMessageBox::information(NULL,"Modification",resultat2);

    }
    else
        QMessageBox::information(NULL,"Modification","Nouveau numero saisie existe deja !");



}

void Abribus::on_Recherchersupp_clicked()
{
    int   Num=ui->Numerorechsupp->currentText().toInt();
     QSqlQuery resultat=existAbribus(Num);

     if(resultat.first())
     {
         ui->Numerosupp->setText(resultat.value(0).toString());
         ui->Nomsupp->setText(resultat.value(1).toString());
         ui->Lieusupp->setText(resultat.value(2).toString());
         ui->Commentairesupp->setText(resultat.value(3).toString());
         ui->etatsupp->setCurrentText(resultat.value(4).toString());
         ui->NomCapteursupp->setText(resultat.value(5).toString());

     }
     else
      {
         QMessageBox::information(NULL,"Recherche","Abribus introuvable");
         on_annulersupp_clicked();
      }


}

void Abribus::on_annulersupp_clicked()
{
    ui->Numerosupp->clear();
    ui->Nomsupp->clear();
    ui->Lieusupp->clear();
    ui->Commentairesupp->clear();
    ui->NomCapteursupp->clear();
    ui->etatsupp->clear();
}

void Abribus::on_supprimer_clicked()
{
    int  Num=ui->Numerorechsupp->currentText().toInt();
    QString N=QString::number(Num);
    QString resultat1="L'abribus du numero ' " +N+" '"+" a été supprimé !";
    QString resultat2="L'abribus du numero ' "+N+" '"+" n'a pas été supprimé !";

     if(deleteAbribus(Num))
      {
         QMessageBox::information(NULL,"Suppression",resultat1);
           on_annulersupp_clicked();
           ui->Numerorechsupp->setModel(this->addtocombo());
           addHistory(Num,"Supression",QDate::currentDate());
      }
     else
        QMessageBox::information(NULL,"Suppression",resultat2);

}


QString Abribus::verifetat(int num)
{
    QSqlQuery query;
    query.prepare("select etat from abribuss where numero=:num");
    query.bindValue(":num",num);
    if(!query.exec())
        qDebug()<<"etat inexistant"<<query.lastError();
    query.next();
        return query.value(0).toString();

}

void Abribus::on_Verifier_clicked()
{
    int num=ui->Numerorechetat->currentText().toInt();
    ui->tableView_etat->setModel(this->status(num));

    if(verifetat(num)=="Allume")
    {
       QPixmap  picture(":/icone/abribus etat/abribus eclairé.png");
       ui->imageetat->setPixmap(picture);
       ui->imageetat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    else
    {
        QPixmap picture(":/icone/abribus etat/abribus vide.png");
        ui->imageetat->setPixmap(picture);
        ui->imageetat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   }

}


QSqlQueryModel* Abribus:: afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT numero,nom,lieu,commentaire,etat,nom_capteur,date_ajout FROM ABRIBUSS");
    QString namecolumn0="Numero";
    QString namecolumn1="Nom";
    QString namecolumn2="Lieu";
    QString namecolumn3="Commentaire";
    QString namecolumn4="Etat";
    QString namecolumn5="Nom Capteur";
    QString namecolumn6="Date_ajout";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    model->setHeaderData(2, Qt::Horizontal,namecolumn2);
    model->setHeaderData(3, Qt::Horizontal, namecolumn3);
    model->setHeaderData(4, Qt::Horizontal,namecolumn4);
    model->setHeaderData(5, Qt::Horizontal, namecolumn5);
    model->setHeaderData(6, Qt::Horizontal,namecolumn6);
    return model;
}

void Abribus:: addHistory(int num, QString act, QDate date)
{
    QString nomut;
    QSqlQuery query2;
    query2.prepare("select pseudo from Connection");
    if(!query2.exec())

        qDebug()<<"recherche utilisateur dans la table  connection error"<<query2.lastError();

    query2.last();
    nomut=query2.value(0).toString();


    QSqlQuery query1;
    query1.prepare("select nom,prenom from utilisateur where pseudo=:pseudo");
    query1.bindValue(":pseudo",nomut);
    if(!query1.exec())

        qDebug()<<"recherche utilisateur error"<<query1.lastError();
    QString ut;
    if(query1.next())
    ut=query1.value(0).toString() +" "+ query1.value(1).toString();

    QSqlQuery query;
    query.prepare("INSERT INTO Historique VALUES(:action,:date_action,:utilisateur,:num,'Abribus')");
    query.bindValue(":action",act);
    query.bindValue(":date_action",date);
    query.bindValue(":utilisateur",ut);
    query.bindValue(":num",num);
    if(!query.exec())
    {
        qDebug()<<"ajuot historique error"<<query.lastError();

    }


}

QSqlQueryModel* Abribus::affichehist(int num,int all)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    if(all==1)
    {
        QString namecolumn3="Abribus Numero";
        model->setHeaderData(3, Qt::Horizontal,namecolumn3);
        query.prepare("Select action,date_action,utilisateur,num from Historique where type_objet='Abribus'");
    }
    else
    {
        query.prepare("Select action,date_action,utilisateur from Historique where ( num=:num and  type_objet='Abribus')");
        query.bindValue(":num",num);
    }
    query.exec();
    if(!query.next())
        qDebug()<<"Erreur recuperation historique"<<query.lastError();
    model->setQuery(query);
    QString namecolumn0="action";
    QString namecolumn1="type action";
    QString namecolumn2="utilisateur";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    model->setHeaderData(2, Qt::Horizontal,namecolumn2);
    return model;
}

void Abribus::on_verifierhist_clicked()
{
    int num=ui->Numerorechhist->currentText().toInt();
    ui->tableView_hist->setModel(affichehist(num,0));
}


QChartView * Abribus :: Stats(int dayy, int monthh, int yearr)
{

    QSqlQuery query;


    QString datee=QString::number(dayy)+"/"+QString::number(monthh)+"/"+QString::number(yearr);
    query.prepare("Select numero,nombre,nom from HISTACTIVITE where ( type='Abribus') ");
    query.bindValue(":date", datee);


    if(!query.exec())
        qDebug()<<"errer recuperation des nombres  des clients"<<query.lastError();
    else
    {
        int i=0;
        QBarSeries *series = new QBarSeries();
        QString categories=" ";
         QBarSet *set0 ;

     while(query.next())
        {
             set0 = new QBarSet(query.value(2).toString());
            *set0 << query.value(1).toInt();
            series->append(set0);
           i++;

        }

     QChart *chart = new QChart();
     chart->addSeries(series);
     chart->setTitle("Les statistiques des abribus le "+datee);
     chart->setAnimationOptions(QChart::SeriesAnimations);


     QBarCategoryAxis *axis = new QBarCategoryAxis();
     axis->append(categories);
     chart->createDefaultAxes();
     chart->setAxisX(axis, series);

     chart->legend()->setVisible(true);
     chart->legend()->setAlignment(Qt::AlignBottom);

     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
     return chartView;
    }

}

void Abribus::on_verfier_stat_clicked()
{
    QGridLayout* layout= new QGridLayout();

    layout->addWidget(Stats(ui->day->currentText().toInt(),ui->month->currentText().toInt(),ui->year->value()),0,0);
    ui->widget->setLayout(layout);
    layout->deleteLater();

}

void Abribus::on_lieu_clicked()
{
    QQuickView *q = new QQuickView();
    q->setSource(QUrl ("qrc:/MAP.qml"));
    q->show();
}
