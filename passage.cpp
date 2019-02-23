#include "passage.h"
#include "ui_passage.h"
#include<QSqlQuery>
#include<QDebug>
#include<QMessageBox>
#include "db.h"
Passage::Passage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Passage)
{
    ui->setupUi(this);
    on_actionAfficher_triggered();
}

Passage::~Passage()
{
    delete ui;
}

void Passage::on_actionQuitter_triggered()
{
    close();
}

void Passage::on_actionAjouter_triggered()
{
    ui->Ajouter->setVisible(true);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->etatajpa->setStyleSheet( "QListView { color: white; }");
}

void Passage::on_actionModifier_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(true);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->Numerorech->setStyleSheet( "QListView { color: white; }");
    ui->etatmo->setStyleSheet( "QListView { color: white; }");
    ui->Numerorech->setModel(addtocombo());

}

void Passage::on_actionSupprimer_triggered()
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

void Passage::on_actionAfficher_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(true);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->tableafficherpa->setModel(afficher());
}

void Passage::on_actionHistorique_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(true);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->numerorechhist->setModel(this->addtocombo());
    ui->numerorechhist->setStyleSheet( "QListView { color: white; }");
    ui->tablehistoriquepa->setModel(affichehist(0,1));
}

void Passage::on_actionEtat_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(true);
    ui->Statistiques->setVisible(false);
    ui->numerorechpa->setModel(this->addtocombo());
    ui->numerorechpa->setStyleSheet( "QListView { color: white; }");
}

void Passage::on_actionStatistiques_triggered()
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


Passage::Passage()
{
    Numero=0;Nom="";Lieu="";Commentaire="";NomCapteur="";etat="";
}
Passage::Passage(int Numero, QString Nom, QString Lieu, QString Commentaire, QString NomCapteur,QString etat)
{
    this->Numero=Numero;
     this->Nom=Nom;
     this->Lieu=Lieu;
     this->Commentaire=Commentaire;
     this->NomCapteur=NomCapteur;
     this->etat=etat;
}



bool Passage :: existnumero(int num )
{
    QSqlQuery query;
    query.prepare("SELECT numero FROM Passage  WHERE numero=:num");
    query.bindValue(":num", num);
    if(!query.exec())
    {
       qDebug() << "verfication numero Passage error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}


bool Passage :: existnomcapteur(QString nom )
{
    QSqlQuery query;
    query.prepare("SELECT nom_capteur FROM Passage WHERE nom_capteur=:nom");
    query.bindValue(":nom", nom);
    if(!query.exec())
    {
       qDebug() << "verfication nom capteur Passage  error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}


QSqlQuery Passage :: existPassage(int num)
{
    QSqlQuery query;
    query.prepare("SELECT numero,nom,lieu,commentaire,etat,nom_capteur FROM Passage WHERE NUMERO=:numero");
    query.bindValue(":numero", num);
    if(!query.exec())
    {
       qDebug() << "Recherche  error:  "<< query.lastError();
    }
    return query;
}

QSqlQueryModel* Passage::addtocombo()
{

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("Select Numero from Passage");
    return model;

}













bool Passage :: ajouter_Passage()
{
    bool success=false;
       QSqlQuery query;
           query.prepare("INSERT INTO passage VALUES (:Numero, :Nom, :Lieu,:Commentaire,:etat,:NomCapteur,sysdate)");
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
               qDebug()<<"Ajout errone";
           return success;
}




bool Passage :: modifier_Passage(int num)
{

QSqlQuery querydelete;
querydelete.prepare("DELETE FROM Passage WHERE Numero=:Numero");
querydelete.bindValue(":Numero", num);
if(!querydelete.exec())
{
        qDebug() << "Modification(supp) passage  error:  "<< querydelete.lastError();
        return false;
}
     QSqlQuery query;
     query.prepare("INSERT INTO passage VALUES (:Numero, :Nom, :Lieu,:Commentaire,:etat,:NomCapteur,sysdate)");
     query.bindValue(":Numero",Numero);
     query.bindValue(":Nom",Nom);
     query.bindValue(":Lieu",Lieu);
     query.bindValue(":Commentaire",Commentaire);
     query.bindValue(":NomCapteur",NomCapteur);
     query.bindValue(":etat",etat);
 if(!query.exec())
 {
         qDebug() << "Modification passage  error:  "<< query.lastError();
         return false;
 }

 return true;

}



bool Passage :: deletePassage(int Numero)
{
    QSqlQuery querydelete;
    querydelete.prepare("DELETE FROM passage WHERE Numero=:Numero");
    querydelete.bindValue(":Numero",Numero);
    if(!querydelete.exec())
    {
            qDebug() << "Suppression passage error:  "<< querydelete.lastError();
            return false;
    }
    return true;
}




QSqlQueryModel* Passage::status(int num)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    query.prepare("Select nom,lieu,etat from Passage where numero=:num");
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







void Passage::on_ajouterpa_clicked()
{

    Numero=ui->numeroajpa->value();
    Nom=ui->nomajpa->text();
    Lieu=ui->lieuajpa->text();
    Commentaire=ui->commentaireajpa->toPlainText();
    etat=ui->etatajpa->currentText();

    QString resultat1="Le passage "+Nom+" a été ajouté !";
    QString resultat2="Le passage "+Nom+" n'a pas été ajouté !";

    if(existnumero(Numero))
        QMessageBox::information(NULL,"Numero","Numero existe deja !");
    else
    {
        if (this->ajouter_Passage())
            {
            QMessageBox::information(NULL,"Ajout",resultat1);
            this->on_annuleraj_clicked();
            addHistory(Numero,"Ajout",QDate::currentDate());
           }
           else
            QMessageBox::information(NULL,"Ajout",resultat2);
    }

}

void Passage::on_annuleraj_clicked()
{
    ui->nomajpa->clear();
    ui->lieuajpa->clear();
    ui->commentaireajpa->clear();
    ui->numeroajpa->clear();
}

void Passage::on_Rechercher_clicked()
{
    int   Num=ui->Numerorech->currentText().toInt();
         QSqlQuery resultat=existPassage(Num);

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
             QMessageBox::information(NULL,"Recherche","Passage introuvable");
             on_annlermo_clicked();
          }
}

void Passage::on_annlermo_clicked()
{
    ui->Numeromo->clear();
    ui->Nommo->clear();
    ui->Lieumo->clear();
    ui->Commentairemo->clear();
    ui->NomCapteurmo->clear();
}




void Passage::on_enregistrer_clicked()
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

        if((!existnumero(Numero)) || (Numero==ui->Numerorech->currentText().toInt()))
        {
            if(modifier_Passage(ui->Numerorech->currentText().toInt()))
               {
                  QMessageBox::information(NULL,"Modification",resultat1);
                  on_annlermo_clicked();
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



void Passage::on_Rechercher_2_clicked()
{
    int   Num=ui->Numerorechsupp->currentText().toInt();
             QSqlQuery resultat=existPassage(Num);

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
                 QMessageBox::information(NULL,"Recherche","Passage introuvable");
                 on_annlersupp_clicked();
              }
}

void Passage::on_annlersupp_clicked()
{
    ui->Numerosupp->clear();
    ui->Nomsupp->clear();
    ui->Lieusupp->clear();
    ui->Commentairesupp->clear();
    ui->NomCapteursupp->clear();
}





void Passage::on_Supprimer_2_clicked()
{
    int  Num=ui->Numerorechsupp->currentText().toInt();
            QString N=QString::number(Num);
            QString resultat1="Le passage  numero ' " +N+" '"+" a été supprimé !";
            QString resultat2="Le assage numero ' "+N+" '"+" n'a pas été supprimé !";

             if(deletePassage(Num))
              {
                 QMessageBox::information(NULL,"Suppression",resultat1);
                   on_annlersupp_clicked();
                   ui->Numerorechsupp->setModel(this->addtocombo());
                   addHistory(Num,"Supression",QDate::currentDate());
              }
             else
                QMessageBox::information(NULL,"Suppression",resultat2);
}




QString Passage::verifetat(int num)
{
    QSqlQuery query;
    query.prepare("select etat from Passage where numero=:num");
    query.bindValue(":num",num);
    if(!query.exec())
        qDebug()<<"etat inexistant"<<query.lastError();
    query.next();
        return query.value(0).toString();
}






void Passage::on_verifieretatpa_clicked()
{
    int num=ui->numerorechpa->currentText().toInt();
            ui->tableetatpa->setModel(this->status(num));
            if(verifetat(num)=="Allume")
            {
               QPixmap  picture(":/icone/passage etat/passage allume.png");
               ui->imagepa->setPixmap(picture);
               ui->imagepa->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            }
            else
            {
                QPixmap picture(":/icone/passage etat/passage eteint.png");
                ui->imagepa->setPixmap(picture);
                ui->imagepa->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
           }
}


QSqlQueryModel* Passage:: afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT numero,nom,lieu,commentaire,etat,nom_capteur,date_ajout FROM Passage ");
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


void Passage:: addHistory(int num,QString act,QDate date)
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
    query.prepare("INSERT INTO Historique VALUES(:action,:date_action,:utilisateur,:num,'Passage')");
    query.bindValue(":action",act);
    query.bindValue(":date_action",date);
    query.bindValue(":utilisateur",ut);
    query.bindValue(":num",num);
    if(!query.exec())
    {
        qDebug()<<"ajuot historique error"<<query.lastError();

    }

}


QSqlQueryModel* Passage::affichehist(int num,int all)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    if(all==1)
    {
        QString namecolumn3="Candelabre Numero";
        model->setHeaderData(3, Qt::Horizontal,namecolumn3);
        query.prepare("Select action,date_action,utilisateur,num from Historique where type_objet='Passage' ");
    }
    else
    {
        query.prepare("Select action,date_action,utilisateur from Historique where (num=:num and type_objet='Passage')");
        query.bindValue(":num",num);
    }
    query.exec();
    query.next();
    model->setQuery(query);
    QString namecolumn0="action";
    QString namecolumn1="type action";
    QString namecolumn2="utilisateur";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    model->setHeaderData(2, Qt::Horizontal,namecolumn2);
    return model;
}




void Passage::on_verifierhist_clicked()
{
    int num=ui->numerorechhist->currentText().toInt();
    ui->tablehistoriquepa->setModel(affichehist(num,0));
}


QChartView * Passage :: Stats(int dayy, int monthh, int yearr)
{

    QSqlQuery query;
    QString datee=QString::number(dayy)+"/"+QString::number(monthh)+"/"+QString::number(yearr);
    query.prepare("Select numero,nombre,nom from HISTACTIVITE where (date_act=:date and type='Passage') ");
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


void Passage::on_verfier_stat_clicked()
{
    QGridLayout* layout= new QGridLayout();
    layout->addWidget(Stats(ui->day->currentText().toInt(),ui->month->currentText().toInt(),ui->year->value()),0,0);
    ui->widget->setLayout(layout);
    layout->deleteLater();

}
