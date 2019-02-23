#include "candelabre.h"
#include "ui_candelabre.h"
#include<QSqlQuery>
#include<QDebug>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QSerialPort>
#include "db.h"
Candelabre::Candelabre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Candelabre)
{
    ui->setupUi(this);
    on_actionAfficher_triggered();
}

Candelabre::~Candelabre()
{
    delete ui;
}


void Candelabre::on_actionEtat_triggered()
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

void Candelabre::on_actionHistorique_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(true);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->numerorechhistc->setModel(this->addtocombo());
    ui->tablehistoriquec->setModel(affichehist(0,1));
     ui->numerorechhistc->setStyleSheet( "QListView { color: white; }");
}

void Candelabre::on_actionAjouter_triggered()
{
    ui->Ajouter->setVisible(true);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->etatajc->setStyleSheet( "QListView { color: white; }");
}

void Candelabre::on_actionModifier_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(true);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->Numerorechmo->setStyleSheet( "QListView { color: white; }");
    ui->etatajc->setStyleSheet( "QListView { color: white; }");
    ui->Numerorechmo->setModel(addtocombo());
}

void Candelabre::on_actionSupprimer_triggered()
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

void Candelabre::on_actionAfficher_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(true);
    ui->Historique->setVisible(false);
    ui->Etat->setVisible(false);
    ui->Statistiques->setVisible(false);
    ui->tableafficherc->setModel(afficher());
}

void Candelabre::on_actionStatistiques_triggered()
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

void Candelabre::on_actionQuitter_triggered()
{
    close();
}

Candelabre ::Candelabre()
{
    Numero=0;Nom="";Lieu="";Commentaire="";NomCapteur="";etat="";NiveauLum=0;
}

Candelabre::Candelabre(int Numero, QString Nom, QString Lieu, QString Commentaire, QString NomCapteur,int NiveauLum,QString etat)
{
    this->Numero=Numero;
     this->Nom=Nom;
     this->Lieu=Lieu;
     this->Commentaire=Commentaire;
     this->NomCapteur=NomCapteur;
    this->NiveauLum=NiveauLum;
     this->etat=etat;
}


bool Candelabre :: existnumero(int num )
{
    QSqlQuery query;
    query.prepare("SELECT numero FROM candelabre WHERE numero=:num");
    query.bindValue(":num", num);
    if(!query.exec())
    {
       qDebug() << "verfication numero candelabre  error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}


bool Candelabre :: existnomcapteur(QString nom )
{
    QSqlQuery query;
    query.prepare("SELECT nom_capteur FROM candelabre WHERE nom_capteur=:nom");
    query.bindValue(":nom", nom);
    if(!query.exec())
    {
       qDebug() << "verfication nom capteur candelabre  error:  "<< query.lastError();
    }
    if(query.first())
        return true;
    else
        return false;
}


QSqlQuery Candelabre :: existCandelabre(int num)
{
    QSqlQuery query;
    query.prepare("SELECT numero,nom,lieu,commentaire,etat,nom_capteur FROM candelabre WHERE NUMERO=:numero");
    query.bindValue(":numero", num);
    if(!query.exec())
    {
       qDebug() << "Recherche  error:  "<< query.lastError();
    }
    return query;
}

QSqlQueryModel* Candelabre::addtocombo()
{

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("Select Numero from candelabre");
    return model;

}


bool Candelabre :: ajouter_Candelabre()
{
    bool success=false;
    QSqlQuery query;
        query.prepare("INSERT INTO Candelabre VALUES (:Numero, :Nom, :Lieu,:Commentaire,:etat,:NomCapteur,5,sysdate)");
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




bool Candelabre :: modifier_Candelabre(int Num)
{

QSqlQuery querydelete;
querydelete.prepare("DELETE FROM Candelabre WHERE Numero=:Numero");
querydelete.bindValue(":Numero", Num);
if(!querydelete.exec())
{
        qDebug() << "Modification(supp) candelabre  error:  "<< querydelete.lastError();
        return false;
}
querydelete.finish();
     QSqlQuery query;
     query.prepare("INSERT INTO Candelabre VALUES (:Numero, :Nom, :Lieu,:Commentaire,:etat,:NomCapteur,5,sysdate)");
     query.bindValue(":Numero",Numero);
     query.bindValue(":Nom",Nom);
     query.bindValue(":Lieu",Lieu);
     query.bindValue(":Commentaire",Commentaire);
     query.bindValue(":NomCapteur",NomCapteur);
     query.bindValue(":etat",etat);
 if(!query.exec())
 {
         qDebug() << "Modification candelabre  error:  "<< query.lastError();
         return false;
 }

 return true;

}


bool Candelabre :: deleteCandelabre(int Num)
{
    QSqlQuery querydelete;
    querydelete.prepare("DELETE FROM candelabre WHERE Numero=:Numero");
    querydelete.bindValue(":Numero",Num);
    if(!querydelete.exec())
    {
            qDebug() << "Suppression candelabre error:  "<< querydelete.lastError();
            return false;
    }
    return true;
}

QSqlQueryModel* Candelabre::status(int num)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    query.prepare("Select nom,lieu,etat,niveau_lumino from candelabre where numero=:num");
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












void Candelabre::on_ajouterc_clicked()
{
        Numero=ui->numeroajc->value();
        Nom=ui->nomajc->text();
        Lieu=ui->lieuajc->text();
        Commentaire=ui->commentaireajc->toPlainText();
        etat=ui->etatajc->currentText();

        QString resultat1="La candelabre "+Nom+" a été ajouté !";
        QString resultat2="La candelabre "+Nom+" n'a pas été ajouté !";

        if(existnumero(Numero))
            QMessageBox::information(NULL,"Numero","Numero existe deja !");
        else
        {
            if (this->ajouter_Candelabre())
                {
                QMessageBox::information(NULL,"Ajout",resultat1);
                this->on_annulerajc_clicked();
                addHistory(Numero,"Ajout",QDate::currentDate());
               }
               else
                QMessageBox::information(NULL,"Ajout",resultat2);
        }

}


void Candelabre::on_annulerajc_clicked()
{
    ui->numeroajc->clear();
    ui->nomajc->clear();
    ui->lieuajc->clear();
    ui->commentaireajc->clear();
}


void Candelabre::on_rechmoc_clicked()
{
    int   Num=ui->Numerorechmo->currentText().toInt();
     QSqlQuery resultat=existCandelabre(Num);

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
         on_annulermoc_clicked();
      }

}

void Candelabre::on_annulermoc_clicked()
{
    ui->Numeromo->clear();
    ui->Nommo->clear();
    ui->Lieumo->clear();
    ui->Commentairemo->clear();
    ui->NomCapteurmo->clear();
    ui->etatmo->clear();

}

void Candelabre::on_enregistrermoc_clicked()
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
        if(modifier_Candelabre(ui->Numerorechmo->currentText().toInt()))
           {
              QMessageBox::information(NULL,"Modification",resultat1);
              on_annulermoc_clicked();
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



void Candelabre::on_rechsuppc_clicked()
{
    int   Num=ui->Numerorechsupp->currentText().toInt();
         QSqlQuery resultat=existCandelabre(Num);

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
             QMessageBox::information(NULL,"Recherche","Candelabre introuvable");
             on_annulersuppc_clicked();
          }


}

void Candelabre::on_annulersuppc_clicked()
{
    ui->Numerosupp->clear();
    ui->Nomsupp->clear();
    ui->Lieusupp->clear();
    ui->Commentairesupp->clear();
    ui->NomCapteursupp->clear();
    ui->etatsupp->clear();
}


void Candelabre::on_supprimerc_clicked()
{
    int  Num=ui->Numerorechsupp->currentText().toInt();
        QString N=QString::number(Num);
        QString resultat1="La candelabre  numero ' " +N+" '"+" a été supprimé !";
        QString resultat2="La candelabre numero ' "+N+" '"+" n'a pas été supprimé !";

         if(deleteCandelabre(Num))
          {
             QMessageBox::information(NULL,"Suppression",resultat1);
               on_annulersuppc_clicked();
               ui->Numerorechsupp->setModel(this->addtocombo());
               addHistory(Num,"Supression",QDate::currentDate());
          }
         else
            QMessageBox::information(NULL,"Suppression",resultat2);
}


QString Candelabre::verifetat(int num)
{
    QSqlQuery query;
    query.prepare("select etat from candelabre where numero=:num");
    query.bindValue(":num",num);
    if(!query.exec())
        qDebug()<<"etat inexistant"<<query.lastError();
    query.next();
        return query.value(0).toString();
}



int Candelabre:: get_niveau(int num)
{
    QSqlQuery query;
    query.prepare("SELECT niveau_lumino from candelabre where numero=:num");
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

bool Candelabre::changerniveau(int nouv,int num)
{
    QSqlQuery query;
    if (nouv==0)
     { query.prepare("Update candelabre SET niveau_lumino=:nouv ,etat='Eteinte' WHERE numero=:num ");}
     else
    {query.prepare("Update candelabre SET niveau_lumino=:nouv,etat='Allume' WHERE numero=:num ");}
    query.bindValue(":nouv",nouv);
    query.bindValue(":num",num);
    if(!query.exec())
    {
        return false;
        qDebug()<<"changement de niveau impossible "<<query.lastError();
    }
    else
        return true;

}

void Candelabre::on_verifieretatc_clicked()
{
    int num=ui->Numerorechetat->currentText().toInt();
        ui->tableetatc->setModel(this->status(num));
        if(verifetat(num)=="Allume")
        {
           QPixmap  picture(":/icone/candelabre etat/candelabre allumé.png");
           ui->imageetatc->setPixmap(picture);
           ui->imageetatc->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
        else
        {
            QPixmap picture(":/icone/candelabre etat/candelabre eteinte.png");
            ui->imageetatc->setPixmap(picture);
            ui->imageetatc->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
       }
        ui->niveau->setRange(0, 10);
        ui->niveau->setValue(get_niveau(num));

}

QSqlQueryModel* Candelabre:: afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT numero,nom,lieu,commentaire,etat,nom_capteur,niveau_lumino,date_ajout FROM Candelabre ");
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

void Candelabre:: addHistory(int num, QString act, QDate date)
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
    query.prepare("INSERT INTO Historique VALUES(:action,:date_action,:utilisateur,:num,'Candelabre')");
    query.bindValue(":action",act);
    query.bindValue(":date_action",date);
    query.bindValue(":utilisateur",ut);
    query.bindValue(":num",num);
    if(!query.exec())
    {
        qDebug()<<"ajuot historique error"<<query.lastError();

    }

}

QSqlQueryModel* Candelabre::affichehist(int num,int all)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    QSqlQuery query;
    if(all==1)
    {
        QString namecolumn3="Candelabre Numero";
        model->setHeaderData(3, Qt::Horizontal,namecolumn3);
        query.prepare("Select action,date_action,utilisateur,num from Historique where type_objet='Candelabre' ");
    }
    else
    {
        query.prepare("Select action,date_action,utilisateur from Historique where (num=:num and type_objet='Candelabre')");
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


void Candelabre::on_verifiercandelabre_clicked()
{
    int num=ui->numerorechhistc->currentText().toInt();
        ui->tablehistoriquec->setModel(affichehist(num,0));
}

void Candelabre::on_Changerniv_clicked()
{
    int num=ui->Numerorechetat->currentText().toInt();
    QSerialPort *a=new QSerialPort;

        int newlev=ui->niveau->value();
        if(newlev!=get_niveau(num))
        {
            if(changerniveau(newlev,num))
            {

                QMessageBox::information(NULL,"Niveau de luminosté","Niveau de luminosité changé à : "+QString::number(newlev));
                 addHistory(num,"Changement de niveau luminosité",QDate::currentDate());
                 niveauarduino(a,QString::number(newlev));

            }

        }
        ui->tableetatc->setModel(this->status(num));
        //on_verifieretatc_clicked();

}

QChartView * Candelabre :: Stats(int dayy, int monthh, int yearr)
{

    QSqlQuery query;
    QString datee=QString::number(dayy)+"/"+QString::number(monthh)+"/"+QString::number(yearr);
    query.prepare("Select numero,nombre,nom from HISTACTIVITE where (date_act=:date and type='Candelabre') ");
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


void Candelabre::on_verfier_stat_clicked()
{
    QGridLayout* layout= new QGridLayout();

    layout->addWidget(Stats(ui->day->currentText().toInt(),ui->month->currentText().toInt(),ui->year->value()),0,0);
    ui->widget->setLayout(layout);
    layout->deleteLater();
}

void Candelabre::niveauarduino(QSerialPort *a, QString ch)
{
    a->write("8");
}

