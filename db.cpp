#include "db.h"
#include <QSqlDatabase>
#include<QString>
#include<QDebug>

db::db(QObject *parent) : QObject(parent)
{

}
db::db()
{

}


 bool db ::  createConnection()
{
        dbs.setHostName("127.0.0.1");
        dbs.setDatabaseName("impactdb");
        dbs.setUserName("impact");
        dbs.setPassword("impact");
        if(dbs.open())
            return true;
        else
        {
            QMessageBox::critical(NULL,"erreur connection bd","erreur bd ");
            return false;
        }
}



 void db::createConnexionArduino()
 {
     arduino_is_available = false;
     arduino_port_name = "";
     arduino = new QSerialPort;
     serialBuffer = "";

     foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
     {
      if(info.hasVendorIdentifier() && info.hasProductIdentifier())
      {
          if(info.vendorIdentifier()==arduino_uno_vendor_id)
          {
              if(info.productIdentifier()==arduino_uno_product_id)
              {
                  arduino_port_name = info.portName();
                  arduino_is_available = true;
              }
          }
      }

     }

     if (arduino_is_available)
     {
         qDebug() <<"arduino is open";
         arduino->setPortName(arduino_port_name);
         arduino->open(QSerialPort::ReadWrite);
         arduino->setBaudRate(QSerialPort::Baud9600);
         arduino->setDataBits(QSerialPort::Data8);
         arduino->setParity(QSerialPort::NoParity);
         arduino->setStopBits(QSerialPort::OneStop);
         arduino->setFlowControl(QSerialPort::NoFlowControl);
         QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
         if (arduino->isWritable())
         {
             qDebug()<<"arduino is writable";
         }
         else qDebug()<<"arduino is not writable";

     }
     else
     {
         qDebug() <<"arduino is not available\n";
     }
 }

 void db:: readSerial()
 {

     serialData = arduino->readAll();
     serialBuffer = QString::fromStdString(serialData.toStdString());
     qDebug()<<serialBuffer;
     QSqlQuery q;
     if (arduino->isWritable())
     {
         if(serialBuffer=="1")
         {
             qDebug()<<q.exec("update HISTACTIVITE set nombre=nombre+1 where numero=1")<<"nombre client incrementé";
         }
         /*else if (serialBuffer=="11")
         {
             qDebug()<<q.exec("update poubelle set etat='Pleine' where numero=1")<<"Etat poubelle changé";
         }
         else if (serialBuffer=="00")
         {
             qDebug()<<q.exec("update poubelle set etat='Vide' where numero=1")<<"Etat poubelle changé";
         }
         else if (serialBuffer=="111")
         {
             q.exec("update passage set etat='Allume' where numero=1");
          }
         else if (serialBuffer=="000")
             q.exec("update passage set etat='Allume' where numero=1");*/

     }

 }

 void db::destructorArduino()
 {
     if(arduino->isOpen())
         arduino->close();
 }







