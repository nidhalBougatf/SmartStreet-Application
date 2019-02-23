#ifndef LED_H
#define LED_H

#include <QMainWindow>

namespace Ui {
class LED;
}

class LED : public QMainWindow
{
    Q_OBJECT

public:
    explicit LED(QWidget *parent = 0);
    ~LED();

private slots:
    void on_actionQuitter_triggered();

    void on_actionEtat_triggered();

    void on_actionHistorique_triggered();

private:
    Ui::LED *ui;
};

#endif // LED_H
