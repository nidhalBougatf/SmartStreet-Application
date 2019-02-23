#ifndef DB_H
#define DB_H
#include <QApplication>
#include <QMessageBox>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSerialPort>
#include <QDebug>
#include <QSerialPortInfo>
#include <QString>
#include <QObject>
#include"candelabre.h"
#include"poteau.h"



class db : public QObject
{
   Q_OBJECT
public:
    db(QObject *parent);
    db();
   bool createConnection();
   void createConnexionArduino();
   void destructorArduino();
   private slots:
       void readSerial();
   private:
       QSerialPort *arduino;
       static const quint16 arduino_uno_vendor_id = 9025;
       static const quint16 arduino_uno_product_id = 67;
       QString arduino_port_name;
       bool arduino_is_available;
       QByteArray serialData;
       QString serialBuffer;

protected:
   QSqlDatabase dbs = QSqlDatabase::addDatabase("QODBC");

};

#endif // DB_H
