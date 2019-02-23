#include "led.h"
#include "ui_led.h"

LED::LED(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LED)
{
    ui->setupUi(this);
}

LED::~LED()
{
    delete ui;
}

void LED::on_actionQuitter_triggered()
{
    close();
}

void LED::on_actionEtat_triggered()
{
    ui->Etat->setVisible(true);
    ui->Historique->setVisible(false);
}

void LED::on_actionHistorique_triggered()
{
    ui->Etat->setVisible(false);
    ui->Historique->setVisible(true);
}
