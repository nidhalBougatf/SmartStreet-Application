#ifndef ARDUINO_H
#define ARDUINO_H
#include <QWidget>
#include <QSerialPort>
#include <QDialog>
#include <QObject>
#include<QString>
#include<QSerialPortInfo>
#include<QDebug>
#include <QByteArray>
#include<QThread>
#include<QtConcurrent/QtConcurrent>

namespace Ui {
class Arduino;
}

class Arduino : public QWidget
{
    Q_OBJECT

public:
    explicit Arduino(QWidget *parent = 0);
    ~Arduino();
    Arduino();
    void lire();
    void ecrire(QString );

private:
    Ui::Arduino *ui;
    QSerialPort *card;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_product_id=67;
    QString arduino_port_name;
    QString command;
    bool arduino_is_available;
signals:
    void detected();

public slots:
    void close();
};

#endif // ARDUINO_H
