#include "arduino.h"
#include "ui_arduino.h"

Arduino::Arduino(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arduino)
{
    ui->setupUi(this);
    arduino_is_available=false;
            arduino_port_name="";
            qDebug() <<"Number of available ports:"<<QSerialPortInfo::availablePorts().length();

            foreach(const QSerialPortInfo & SerialPortInfo,QSerialPortInfo::availablePorts())
            {
                //qDebug()<<"Has Vendor ID:"<<SerialPortInfo.hasVendorIdentifier();
                if(SerialPortInfo.hasVendorIdentifier())
                {
                   //qDebug()<<"Vendor ID:"<<SerialPortInfo.vendorIdentifier();
                }
                //qDebug()<<"Has Product ID:"<<SerialPortInfo.hasProductIdentifier();
                if(SerialPortInfo.hasProductIdentifier())
                {
                   //qDebug()<<"Product ID:"<<SerialPortInfo.productIdentifier();
                }
            }


            foreach(const QSerialPortInfo & serialPortInfo,QSerialPortInfo::availablePorts())
                if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
                {

                    if(serialPortInfo.vendorIdentifier()==arduino_uno_vendor_id)
                    {
                        if(serialPortInfo.productIdentifier()==arduino_uno_product_id)
                          arduino_port_name=serialPortInfo.portName();
                        arduino_is_available=true;

                    }


                    if(arduino_is_available)
                    {
                       card= new QSerialPort();
                       card->setPortName(arduino_port_name);
                       card->open(QSerialPort::ReadWrite);
                       card->setBaudRate(QSerialPort::Baud9600);
                       card->setDataBits(QSerialPort::Data8);
                       card->setParity(QSerialPort::NoParity);
                       card->setStopBits(QSerialPort::OneStop);
                       card->setFlowControl(QSerialPort::NoFlowControl);

                    }
                    else
                    {
                    QMessageBox::warning(NULL,"Port error","couldn't find the arduino");
                    }
                 }
                //QFuture<void> future=QtConcurrent::run(this,Arduino::lire);
                //connect(abriantipluis,SIGNAL(activer()),this,SLOT(activerAbri()));

}

Arduino::~Arduino()
{
    delete ui;
}

void Arduino  :: close()
{
    if(card->isOpen())
    {
       card->close();
    }
}





void Arduino::lire()
{
    QString ch;
    bool lecture=true;
    while(lecture)
    {
       card->waitForReadyRead(1000);
        if(card->isReadable())
        {

            QStringList b= ch.split(",");
            if(b.length()<3)
            {
                QByteArray a=card->readAll();
                ch += QString::fromStdString(a.toStdString());
                qDebug()<<ch;
            }
            else
            {

                ch="";
            }
            qDebug()<<ch;
        }
        else
        {
            qDebug()<<"Couldn't read from serial!";
            lecture=false;
        }
    }
}



void Arduino::ecrire(QString msg)
{


        if(card->isWritable())
        {
            card->write(msg.toStdString().c_str());
            card->flush();
            QThread::currentThread()->msleep(100);
            qDebug()<<msg.toStdString().c_str();
        }
        else
        {
            qDebug() << "Couldn't write to serial!";
        }
}
/*void Arduino::activerAbri()
{
    QFuture<void> future=QtConcurrent::run(this,Arduino::ecrire,QString("a"));
}*/


