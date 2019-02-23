#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QMainWindow>
#include <QWidget>
#include<QSystemTrayIcon>
namespace Ui {
class Notification;
}

class Notification : public QWidget
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent = 0);
    ~Notification();
    void shownotif(QString titre, QString msg, int type);

private:
    Ui::Notification *ui;
    QSystemTrayIcon *notify;
};

#endif // NOTIFICATION_H
