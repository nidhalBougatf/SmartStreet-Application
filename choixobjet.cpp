#include "choixobjet.h"
#include "ui_choixobjet.h"

Choixobjet::Choixobjet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Choixobjet)
{
    ui->setupUi(this);
}

Choixobjet::~Choixobjet()
{
    delete ui;
}



void Choixobjet::on_pushButton_clicked()
{
    abribus = new Abribus(this);
    abribus->show();
}

void Choixobjet::on_pushButton_2_clicked()
{
    candelabre = new Candelabre(this);
    candelabre->show();
}

void Choixobjet::on_pushButton_3_clicked()
{
    passage = new Passage(this);
    passage->show();
}

void Choixobjet::on_pushButton_4_clicked()
{
    poubelle = new Poubelle(this);
    poubelle->show();
}

void Choixobjet::on_pushButton_5_clicked()
{
    poteau = new Poteau(this);
     poteau->show();
}
