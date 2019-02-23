#include "choix.h"
#include "ui_choix.h"

Choix::Choix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Choix)
{
    ui->setupUi(this);
}

Choix::~Choix()
{
    delete ui;
}




void Choix::on_pushButton_2_clicked()
{
    employee = new Employee(this);
    employee->show();

}

void Choix::on_pushButton_clicked()
{
    choixobjet = new Choixobjet(this);
     choixobjet->show();
}
