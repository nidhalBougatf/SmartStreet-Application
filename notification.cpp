#include "notification.h"
#include "ui_notification.h"

Notification::Notification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Notification)
{
    ui->setupUi(this);
    notify=new QSystemTrayIcon(this);
    notify->setIcon(QIcon(":/icone/iconenotif.png"));
    notify->show();
}

Notification::~Notification()
{
    delete ui;
}


void Notification::shownotif(QString titre,QString msg,int type)
{

    int duree=1000;
    switch (type)
    {
        case 1 : notify->showMessage(titre,msg,QSystemTrayIcon::Information,duree);break;
        case 2 : notify->showMessage(titre,msg,QSystemTrayIcon::Critical ,duree);break;
        case 3 : notify->showMessage(titre,msg,QSystemTrayIcon::Warning ,duree);break;
    }
    notify->show();

}
