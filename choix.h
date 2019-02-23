#ifndef CHOIX_H
#define CHOIX_H

#include <QMainWindow>
#include"employee.h"
#include"choixobjet.h"
namespace Ui {
class Choix;
}

class Choix : public QMainWindow
{
    Q_OBJECT

public:
    explicit Choix(QWidget *parent = 0);
    ~Choix();

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Choix *ui;
    Employee *employee;
    Choixobjet *choixobjet;


};

#endif // CHOIX_H
