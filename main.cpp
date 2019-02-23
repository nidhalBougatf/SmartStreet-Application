#include "mainwindow.h"
#include <QApplication>
#include<QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(253,1,1));
    p.setColor(QPalette::WindowText, QColor(255,255,255));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    qApp->setPalette(p);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
