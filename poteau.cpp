#include "poteau.h"
#include "ui_poteau.h"
#include<QMessageBox>
#include "db.h"
#include<QDebug>
Poteau::Poteau(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Poteau)
{
    ui->setupUi(this);
    on_actionAfficher_triggered();
}

Poteau::~Poteau()
{
    delete ui;
}

void Poteau::on_actionAjouter_triggered()
{
    ui->Ajouter->setVisible(true);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->etatajpo->setStyleSheet( "QListView { color: white; }");
}

void Poteau::on_actionModifier_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(true);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->Numerorechmo->setStyleSheet( "QListView { color: white; }");
    ui->etatajpo->setStyleSheet( "QListView { color: white; }");
    ui->Numerorechmo->setModel(addtocombo());
}

void Poteau::on_actionSupprimer_triggered()
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

void Poteau::on_actionAfficher_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(true);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->tableafficherpo->setModel(afficher());
}

void Poteau::on_actionHistorique_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(true);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->numerorechhistpo->setModel(this->addtocombo());
    ui->numerorechhistpo->setStyleSheet( "QListView { color: white; }");
    ui->tablehistoriquepo->setModel(affichehist(0,1));

}

void Poteau::on_actionEtat_triggered()
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

void Poteau::on_actionStatistiques_triggered()
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


void Poteau::on_actionQuitter_triggered()
{
    close();
}

Poteau ::Poteau()
{
    Numero=0;Nom="";Lieu="";Commentaire="";NomCapteur="";etat="";NiveauLum=0;date_po=QDate::currentDate();
}


Poteau::Poteau(int Numero, QString Nom, QString Lieu, QString Commentaire, QString NomCapteur,QString etat)
{
    this->Numero=Numero;
     this->Nom=Nom;
     this->Lieu=Lieu;
     this->Commentaire=Commentaire;
     this->NomCapteur=NomCapteur;
     this->etat=etat;
}


bool Poteau :: existnumero(int num )
{
    QSqlQuery query;
    query.prepare("SELECT numero FROM poteau WHERE numero=:num");
    query.bindValue(":num", num);
    if(!query.exec())
    {
       qDebug() << "verfication numero poteau error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}


bool Poteau :: existnomcapteur(QString nom )
{
    QSqlQuery query;
    query.prepare("SELECT nom_capteur FROM Poteau WHERE nom_capteur=:nom");
    query.bindValue(":nom", nom);
    if(!query.exec())
    {
       qDebug() << "verfication nom capteur Poteau  error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}


QSqlQuery Poteau :: existPoteau(int num)
{
    QSqlQuery query;
    query.prepare("SELECT numero,nom,lieu,commentaire,etat,nom_capteur FROM Poteau WHERE NUMERO=:numero");
    query.bindValue(":numero", num);
    if(!query.exec())
    {
       qDebug() << "Recherche  error:  "<< query.lastError();
    }
    return query;
}

QSqlQueryModel* Poteau::addtocombo()
{

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("Select Numero from Poteau");
    return model;
}


bool Poteau :: ajouter_Poteau()
{
    bool success=false;
    QSqlQuery query;
        query.prepare("INSERT INTO Poteau VALUES (:Numero, :Nom, :Lieu,:Commentaire,:etat,:NomCapteur,5,sysdate)");
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





bool Poteau :: modifier_Poteau(int Num)
{

QSqlQuery querydelete;
querydelete.prepare("DELETE FROM Poteau WHERE Numero=:Numero");
querydelete.bindValue(":Numero", Num);
if(!querydelete.exec())
{
        qDebug() << "Modification(supp) Poteau error:  "<< querydelete.lastError();
        return false;
}
querydelete.finish();
     QSqlQuery query;
     query.prepare("INSERT INTO Poteau VALUES (:Numero, :Nom, :Lieu,:Commentaire,:etat,:NomCapteur,5,sysdate)");
     query.bindValue(":Numero",Numero);
     query.bindValue(":Nom",Nom);
     query.bindValue(":Lieu",Lieu);
     query.bindValue(":Commentaire",Commentaire);
     query.bindValue(":NomCapteur",NomCapteur);
     query.bindValue(":etat",etat);
 if(!query.exec())
 {
         qDebug() << "Modification Poteau  error:  "<< query.lastError();
         return false;
 }
 return true;

}

bool Poteau :: deletePoteau(int Num)
{
    QSqlQuery querydelete;
    querydelete.prepare("DELETE FROM Poteau WHERE Numero=:Numero");
    querydelete.bindValue(":Numero",Num);
    if(!querydelete.exec())
    {
            qDebug() << "Suppression Poteau error:  "<< querydelete.lastError();
            return false;
    }
    return true;
}



QSqlQueryModel* Poteau::status(int num)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    query.prepare("Select nom,lieu,etat,niveau_lumino_p from Poteau where numero=:num");
    query.bindValue(":num",num);
    query.exec();
    model->setQuery(query);
    QString namecolumn0="Nom";
    QString namecolumn1="Lieu";
    QString namecolumn2="Etat";
    QString namecolumn3="Niveau actuelle";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    model->setHeaderData(2, Qt::Horizontal,namecolumn2);
    model->setHeaderData(3, Qt::Horizontal,namecolumn3);
    return model;
}




void Poteau::on_ajouterpo_clicked()
{
    Numero=ui->numeroajpo->value();
    Nom=ui->nomajpo->text();
    Lieu=ui->lieuajpo->text();
    Commentaire=ui->commentaireajpo->toPlainText();
    etat=ui->etatajpo->currentText();
    QString resultat1="Le Poteau "+Nom+" a été ajouté !";
    QString resultat2="Le Poteau "+Nom+" n'a pas été ajouté !";

           if(existnumero(Numero))
               QMessageBox::information(NULL,"Numero","Numero existe deja !");
           else
           {
               if (this->ajouter_Poteau())
                   {
                   QMessageBox::information(NULL,"Ajout",resultat1);
                   this->on_annulerajpo_clicked();
                   addHistory(Numero,"Ajout",QDate::currentDate());
                  }
                  else
                   QMessageBox::information(NULL,"Ajout",resultat2);
           }

}



void Poteau::on_annulerajpo_clicked()
{
    ui->numeroajpo->clear();
    ui->nomajpo->clear();
    ui->lieuajpo->clear();
    ui->commentaireajpo->clear();
}



void Poteau::on_rechmopo_clicked()
{
    int   Num=ui->Numerorechmo->currentText().toInt();
         QSqlQuery resultat=existPoteau(Num);

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
             QMessageBox::information(NULL,"Recherche","Poteau introuvable");
             on_annulermopo_clicked();
          }
}




void Poteau::on_annulermopo_clicked()
{
    ui->Numeromo->clear();
    ui->Nommo->clear();
    ui->Lieumo->clear();
    ui->Commentairemo->clear();
    ui->NomCapteurmo->clear();
    ui->etatmo->clear();
}



void Poteau::on_enregistrermopo_clicked()
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

        if((!existnumero(Numero)) || (Numero==ui->Numerorechmo->currentText().toInt()))
        {
            if(modifier_Poteau(ui->Numerorechmo->currentText().toInt()))
               {
                  QMessageBox::information(NULL,"Modification",resultat1);
                  on_annulermopo_clicked();
                  if(ui->Numerorechmo->currentText().toInt()!=Numero)
                  {

                      addHistory(ui->Numerorechmo->currentText().toInt(),"Supression",QDate::currentDate());
                      addHistory(Numero,"Ajout",QDate::currentDate());

                  }
                  else
                      addHistory(ui->Numerorechmo->currentText().toInt(),"Modification",QDate::currentDate());

               }
            else
                QMessageBox::information(NULL,"Modification",resultat2);

        }
        else
            QMessageBox::information(NULL,"Modification","Nouveau numero saisie existe deja !");

}





void Poteau::on_rechsupppo_clicked()
{
    int   Num=ui->Numerorechsupp->currentText().toInt();
             QSqlQuery resultat=existPoteau(Num);

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
                 QMessageBox::information(NULL,"Recherche","Poteau introuvable");
                 on_annulersupppo_clicked();
              }
}

void Poteau::on_annulersupppo_clicked()
{
    ui->Numerosupp->clear();
    ui->Nomsupp->clear();
    ui->Lieusupp->clear();
    ui->Commentairesupp->clear();
    ui->NomCapteursupp->clear();
    ui->etatsupp->clear();
}



void Poteau::on_supprimerpo_clicked()
{
    int  Num=ui->Numerorechsupp->currentText().toInt();
            QString N=QString::number(Num);
            QString resultat1="Le Poteau numero ' " +N+" '"+" a été supprimé !";
            QString resultat2="Le Poteau numero ' "+N+" '"+" n'a pas été supprimé !";

             if(deletePoteau(Num))
              {
                 QMessageBox::information(NULL,"Suppression",resultat1);
                   on_annulersupppo_clicked();
                   ui->Numerorechsupp->setModel(this->addtocombo());
                   addHistory(Num,"Supression",QDate::currentDate());
              }
             else
                QMessageBox::information(NULL,"Suppression",resultat2);

}


QString Poteau::verifetat(int num)
{
    QSqlQuery query;
    query.prepare("select etat from Poteau where numero=:num");
    query.bindValue(":num",num);
    if(!query.exec())
        qDebug()<<"etat inexistant"<<query.lastError();
    query.next();
        return query.value(0).toString();
}

int Poteau:: get_niveau(int num)
{
    QSqlQuery query;
    query.prepare("SELECT niveau_lumino_p from Poteau where numero=:num");
    query.bindValue(":num",num);
    if(!query.exec())
    {
       return -1;
        qDebug()<<"recperation de niveau impossible"<<query.last();
    }
    else
    {
        query.next();
        return query.value(0).toInt();
    }
}




void Poteau::on_verifieretatpo_clicked()
{
       int num=ui->Numerorechetat->currentText().toInt();
            ui->tableetatpo->setModel(this->status(num));
            if(verifetat(num)=="Allume")
            {
               QPixmap  picture(":/icone/poteau etat/gyro.png");
               ui->imageetatpo->setPixmap(picture);
               ui->imageetatpo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            }
            else
            {
                QPixmap picture(":/icone/poteau etat/poteau eteintn.png");
                ui->imageetatpo->setPixmap(picture);
                ui->imageetatpo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
           }
            ui->niveau->setRange(0, 10);
            ui->niveau->setValue(get_niveau(num));
}

QSqlQueryModel*  Poteau :: afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT numero,nom,lieu,commentaire,etat,nom_capteur,niveau_lumino_p,date_ajout FROM Poteau ");
    QString namecolumn0="Numero";
    QString namecolumn1="Nom";
    QString namecolumn2="Lieu";
    QString namecolumn3="Commentaire";
    QString namecolumn4="Etat";
    QString namecolumn5="Nom Capteur";
    QString namecolumn6="Luminosité actuelle";
    QString namecolumn7="Date_ajout";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    model->setHeaderData(2, Qt::Horizontal,namecolumn2);
    model->setHeaderData(3, Qt::Horizontal, namecolumn3);
    model->setHeaderData(4, Qt::Horizontal,namecolumn4);
    model->setHeaderData(5, Qt::Horizontal, namecolumn5);
    model->setHeaderData(6, Qt::Horizontal,namecolumn6);
    model->setHeaderData(7, Qt::Horizontal,namecolumn7);
    return model;
}



void Poteau:: addHistory(int num, QString act, QDate date)
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
    query.prepare("INSERT INTO Historique VALUES(:action,:date_action,:utilisateur,:num,'Poteau')");
    query.bindValue(":action",act);
    query.bindValue(":date_action",date);
    query.bindValue(":utilisateur",ut);
    query.bindValue(":num",num);
    if(!query.exec())
    {
        qDebug()<<"ajuot historique error"<<query.lastError();

    }

}




QSqlQueryModel* Poteau::affichehist(int num,int all)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    if(all==1)
    {
        QString namecolumn3="Candelabre Numero";
        model->setHeaderData(3, Qt::Horizontal,namecolumn3);
        query.prepare("Select action,date_action,utilisateur,num from Historique where type_objet='Poteau' ");
    }
    else
    {
        query.prepare("Select action,date_action,utilisateur from Historique where (num=:num and type_objet='Poteau')");
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



void Poteau::on_verifiercandelabre_clicked()
{
    int num=ui->numerorechhistpo->currentText().toInt();
    ui->tablehistoriquepo->setModel(affichehist(num,0));
}


QChartView * Poteau :: Stats(int dayy, int monthh, int yearr)
{

    QSqlQuery query;
    QString datee=QString::number(dayy)+"/"+QString::number(monthh)+"/"+QString::number(yearr);
    query.prepare("Select numero,nombre,nom from HISTACTIVITE where (date_act=:date and type='Poteau') ");
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


void Poteau::on_verfier_stat_clicked()
{
    QGridLayout* layout= new QGridLayout();

    layout->addWidget(Stats(ui->day->currentText().toInt(),ui->month->currentText().toInt(),ui->year->value()),0,0);
    ui->widget->setLayout(layout);
    layout->deleteLater();
}

