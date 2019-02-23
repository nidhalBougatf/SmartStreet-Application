#include "employee.h"
#include "ui_employee.h"
#include"db.h"

#include<ctime>
#include<cstdlib>

#define alphanum "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define stringLength  (sizeof(alphanum)-1 )

Employee::Employee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
    on_actionAfficher_triggered();
}

Employee::~Employee()
{
    delete ui;
}

void Employee::on_actionAjouter_triggered()
{
    ui->Ajouter->setVisible(true);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->fonctionaj->setStyleSheet( "QListView { color: white; }");
    ui->typeaj->setStyleSheet( "QListView { color: white; }");

}

void Employee::on_actionModifier_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(true);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->pseudomo->setReadOnly(true);
    ui->fonctionmo->setStyleSheet( "QListView { color: white; }");
    ui->typemo->setStyleSheet( "QListView { color: white; }");
}

void Employee::on_actionSupprimer_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(true);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(false);
    ui->pseudosupp->setReadOnly(true);
    ui->nomsupp->setReadOnly(true);
    ui->prenomsupp->setReadOnly(true);
    ui->cinsupp->setReadOnly(true);
    ui->mdpsupp->setReadOnly(true);
    ui->typesupp->setDisabled(true);
    ui->fonctionsupp->setDisabled(true);

}

void Employee::on_actionAfficher_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(true);
    ui->Historique->setVisible(false);
    ui->tableutilisateur->setModel(this->afficher());
}

void Employee::on_actionHistorique_triggered()
{
    ui->Ajouter->setVisible(false);
    ui->Modifier->setVisible(false);
    ui->Supprimer->setVisible(false);
    ui->Afficher->setVisible(false);
    ui->Historique->setVisible(true);
    ui->pseudoverif->setStyleSheet( "QListView { color: white; }");
    ui->pseudoverif->setModel(this->addtocombo());
    ui->tablehistorique->setModel(afficherhistorique("",1));
}

void Employee::on_actionQuitter_triggered()
{
    close();
}


Employee :: Employee ( QString nom, QString prenom, QString pseudo, QString mdp , QString fonction, QString type,QString CIN)
{
    this->nom=nom;
    this->prenom=prenom;
    this->pseudo=pseudo;
    this->mdp=mdp;
    this->fonction=fonction;
    this->type=type;
    this->CIN=CIN;

}

QSqlQueryModel* Employee::addtocombo()
{

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("Select pseudo from utilisateur");
    return model;

}

bool Employee :: addEmployee()
{

QSqlQuery query;
query.prepare("INSERT INTO UTILISATEUR  VALUES (:pseudo,:nom,:prenom,:mdp,:fonction,:type,:CIN)");

query.bindValue(":pseudo", pseudo);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":mdp", mdp);
query.bindValue(":fonction",fonction);
query.bindValue(":type",type);
query.bindValue(":CIN",CIN);

if(!query.exec())
{
    qDebug() << "Ajout utilisateur  error:  "<< query.lastError();
    return false;
}
return true;
}



bool Employee :: editEmployee(QString pseudoo)
{

QSqlQuery querydelete;
querydelete.prepare("DELETE FROM UTILISATEUR WHERE pseudo=:pseudo");
querydelete.bindValue(":pseudo", pseudoo);
if(!querydelete.exec())
{
        qDebug() << "Modification(supp) utilisateur  error:  "<< querydelete.lastError();
        return false;
}
     QSqlQuery query;
     query.prepare("INSERT INTO UTILISATEUR  VALUES (:pseudo,:nom,:prenom,:mdp,:fonction,:type,:CIN)");
     query.bindValue(":pseudo", pseudo);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom", prenom);
     query.bindValue(":mdp", mdp);
     query.bindValue(":fonction",fonction);
     query.bindValue(":type",type);
     query.bindValue(":CIN",CIN);
 if(!query.exec())
 {
         qDebug() << "Modification utilisateur  error:  "<< query.lastError();
         return false;
 }

 return true;

}

bool Employee :: deleteEmployee(QString pseudoo)
{
    QSqlQuery querydelete;
    querydelete.prepare("DELETE FROM UTILISATEUR WHERE pseudo=:pseudo");
    querydelete.bindValue(":pseudo", pseudoo);
    if(!querydelete.exec())
    {
            qDebug() << "Suppression utilisateur  error:  "<< querydelete.lastError();
            return false;
    }
    return true;
}

QSqlQueryModel* Employee :: afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM UTILISATEUR");
    QString namecolumn0="Pseudo";
    QString namecolumn1="Nom";
    QString namecolumn2="Prenom";
    QString namecolumn3="CIN";
    QString namecolumn4="MotDePasse";
    QString namecolumn5="Fonction";
    QString namecolumn6="Type";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    model->setHeaderData(2, Qt::Horizontal,namecolumn2);
    model->setHeaderData(3, Qt::Horizontal, namecolumn3);
    model->setHeaderData(4, Qt::Horizontal,namecolumn4);
    model->setHeaderData(5, Qt::Horizontal, namecolumn5);
    model->setHeaderData(6, Qt::Horizontal,namecolumn6);
    return model;

}


bool Employee :: verifEmployee(QString pseudoo)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM UTILISATEUR WHERE pseudo=:pseudo");
    query.bindValue(":pseudo", pseudoo);
    if(!query.exec())
    {
       qDebug() << "Verif error:  "<< query.lastError();
       return false;
    }

    if(query.first())
        {
            return true;
        }

    return false;

}

QSqlQuery Employee :: existEmployee(QString pseudoo )
{
    QSqlQuery query;
    query.prepare("SELECT * FROM UTILISATEUR WHERE pseudo=:pseudo");
    query.bindValue(":pseudo", pseudoo);
    if(!query.exec())
    {
       qDebug() << "Recherche  error:  "<< query.lastError();
    }
    return query;
}



void Employee::on_Enregistrer_clicked()
{
    this->nom = ui->nomaj->text();
    this->prenom = ui->prenomaj->text();
    this->pseudo = ui->pseudoaj->text();
    this->mdp = ui->mdpaj->text();
    this->CIN = ui->cinaj->text();
    this->fonction=ui->fonctionaj->currentText();
    this->type = ui->typeaj->currentText();
    QString resultat1="L'"+type+ " ' " +pseudo+" '"+" a été ajouté !";
    QString resultat2="L'"+type+" '"+pseudo+" '"+" n'a pas été ajouté !";

        if(!verifEmployee(pseudo))
        {
           if(this->addEmployee())
           {
            QMessageBox::information(NULL,"Ajout",resultat1);
            this->on_Annuler_clicked();
           }
           else
            QMessageBox::information(NULL,"Ajout",resultat2);
        }
    else
        QMessageBox::information(NULL,"Ajout","Pseudo existe déjà !");


}


void Employee::on_RechercherModif_clicked()
{
    QString pseudoo=ui->pseudorech->text();
    QSqlQuery resultat=existEmployee(pseudoo);
    if(resultat.first())
    {
        ui->pseudomo->setText(resultat.value(0).toString());
        ui->nommo->setText(resultat.value(1).toString());
        ui->prenomo->setText(resultat.value(2).toString());
        ui->mdpmo->setText(resultat.value(3).toString());
        ui->fonctionmo->setCurrentText(resultat.value(4).toString());
        ui->typemo->setCurrentText(resultat.value(5).toString());
        ui->cinmo->setText(resultat.value(6).toString());
    }
    else
     {
        QMessageBox::information(NULL,"Recherche","Utilisateur introuvable");
        on_Annuler_2_clicked();
     }
}



void Employee::on_Sauvegarder_clicked()
{
    this->nom = ui->nommo->text();
    this->prenom = ui->prenomo->text();
    this->pseudo = ui->pseudomo->text();
    this->mdp = ui->mdpmo->text();
    this->CIN = ui->cinmo->text();
    this->fonction=ui->fonctionmo->currentText();
    this->type = ui->typemo->currentText();
    QString resultat1="Les données de " +pseudo+" '"+" ont été modifié !";
    QString resultat2="Les données de "+pseudo+" '"+" n'ont pas été modififé !";

          if(editEmployee(ui->pseudorech->text()))
         {
          QMessageBox::information(NULL,"Modification",resultat1);
          on_Annuler_clicked();
        }
       else
        QMessageBox::information(NULL,"Modification",resultat2);

}


void Employee::on_rechsupp_clicked()
{

    QString pseudoo=ui->pseudorechsupp->text();
    QSqlQuery resultat=existEmployee(pseudoo);

        if(resultat.first())
        {
            ui->pseudosupp->setText(resultat.value(0).toString());
            ui->nomsupp->setText(resultat.value(1).toString());
            ui->prenomsupp->setText(resultat.value(2).toString());
            ui->mdpsupp->setText(resultat.value(3).toString());
            ui->fonctionsupp->setCurrentText(resultat.value(4).toString());
            ui->typesupp->setCurrentText(resultat.value(5).toString());
            ui->cinsupp->setText(resultat.value(6).toString());
        }
        else
         {
            QMessageBox::information(NULL,"Recherche","Utilisateur introuvable");
            on_Annuler_3_clicked();
         }

}


void Employee::on_Supprime_clicked()
{
    QString pseudoo=ui->pseudorechsupp->text();
    QString resultat1="L'utilisateur ' " +pseudoo+" '"+" a été supprimé !";
    QString resultat2="L'utilisateur ' "+pseudoo+" '"+"n'a pas été supprimé !";

            if(pseudoo!="")
            {
                if(deleteEmployee(pseudoo))
                {
                 QMessageBox::information(NULL,"Suppression",resultat1);
                 on_Annuler_3_clicked();
                }
                else
                 QMessageBox::information(NULL,"Suppression",resultat2);

          }
    else
       QMessageBox::information(NULL,"Suppression","Vous n'avez pas saisi un pseudo !");

}



void Employee::on_Annuler_clicked()
{
    ui->nomaj->clear();
    ui->prenomaj->clear();
    ui->pseudoaj->clear();
    ui->cinaj->clear();
    ui->mdpaj->clear();
}


void Employee::on_Annuler_2_clicked()
{
    ui->nommo->clear();
    ui->prenomo->clear();
    ui->pseudomo->clear();
    ui->cinmo->clear();
    ui->mdpmo->clear();
}

void Employee::on_Annuler_3_clicked()
{

    ui->nomsupp->clear();
    ui->prenomsupp->clear();
    ui->pseudosupp->clear();
    ui->cinsupp->clear();
    ui->mdpsupp->clear();

}






QSqlQueryModel* Employee :: afficherhistorique(QString pseudoo,int all)
{

    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;
    if(all==1)
    query.prepare("Select * from CONNECTION");
    else
    {
        query.prepare("Select * from CONNECTION where pseudo=:pseudo");
        query.bindValue(":pseudo",pseudoo);
    }
    if(!query.exec())
        qDebug()<<"recuperation de l'historique de connexion erreur"<<query.lastError();
    if(!query.first())
        QMessageBox::critical(NULL,"Attention","L'utilisateur  "+pseudoo+"  n'a jaimais utiliser l'application !");
    model->setQuery(query);
    QString namecolumn0="Pseudo";
    QString namecolumn1="Date de connexion";
    model->setHeaderData(0, Qt::Horizontal,namecolumn0);
    model->setHeaderData(1, Qt::Horizontal, namecolumn1);
    return model;

}



void Employee::on_verifier_clicked()
{
    QString pseudoo=ui->pseudoverif->currentText();
    ui->tablehistorique->setModel(afficherhistorique(pseudoo,0));
}

















































char genRandom()
{

   unsigned int x=rand()% stringLength;
    return alphanum[x];
}


void Employee::on_actionDelt_Gen_triggered()
{

        QSqlQuery query;
        query.prepare("DELETE FROM UTILISATEUR  WHERE ((pseudo !='a') and (pseudo!='z'))");

        if(!query.exec())
        {
            qDebug() << "Supression utilisateur genere automatiquement  error:  "<< query.lastError();

        }
        else
            QMessageBox::information(NULL,"Suppression","Suppression reussie !");


}

void Employee::on_actionAuto_Gen_triggered()
{


         /*int randomYear,randomMonth,randomDays;
         srand (time(NULL));
         randomYear = (rand()%2016)+2010;
         randomMonth = (rand()%12)+1;
         randomDays = (rand()%30)+1;
         QString date=randomYear.toString()+"/"+randomMonth.toString()+"/"+randomDays.toString();*/


         QString fonct[2] = {"Technicien", "Policier"};
         QString typ[2] = {"Administrateur", "Employee"};
         QString pseudo,nom,prenom,mdp,fonction,type;
         int CIN,RandIndex;
         srand(time(0));

         for(int i=0;i<10;i++)
         {
             mdp="";
             pseudo="";
             nom="";
             prenom="";
             CIN=1;

              for(unsigned int i=0;i<=6;i++)
               {
                  CIN=CIN*(rand()%9+1);
               }

             for(unsigned int j = 0; j < 7; j++)
             {
               pseudo += genRandom();
             }

             for(unsigned int j = 0; j < 7; j++)
             {
               nom += genRandom();
             }

             for(unsigned int j = 0; j < 7; j++)
             {
               prenom += genRandom();
             }


             for(unsigned int j = 0; j < 7; j++)
             {
               mdp+= genRandom();
             }

             RandIndex = rand() % 2;
             fonction=fonct[RandIndex];

              RandIndex = rand() % 2;
             type=typ[RandIndex];

             QSqlQuery query;
             query.prepare("INSERT INTO UTILISATEUR  VALUES (:pseudo,:nom,:prenom,:mdp,:fonction,:type,:CIN)");

             query.bindValue(":pseudo", pseudo);
             query.bindValue(":nom", nom);
             query.bindValue(":prenom", prenom);
             query.bindValue(":mdp", mdp);
             query.bindValue(":fonction",fonction);
             query.bindValue(":type",type);
             query.bindValue(":CIN",CIN);

             if(!query.exec())
             {
                 qDebug() << "generation des données utilisateur  error:  "<< query.lastError();

             }

         }

}
