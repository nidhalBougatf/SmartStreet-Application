#ifndef CHOIXOBJET_H
#define CHOIXOBJET_H

#include <QMainWindow>
#include"poubelle.h"
#include"candelabre.h"
#include"passage.h"
#include"abribus.h"
#include"poteau.h"
namespace Ui {
class Choixobjet;
}

class Choixobjet : public QMainWindow
{
    Q_OBJECT

public:
    explicit Choixobjet(QWidget *parent = 0);
    ~Choixobjet();

private slots:



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Choixobjet *ui;
    Candelabre *candelabre;
    Poubelle *poubelle;
    Passage *passage;
    Abribus *abribus;
    Poteau *poteau;




};

#endif // CHOIXOBJET_H
