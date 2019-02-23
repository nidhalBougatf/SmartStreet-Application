#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T23:26:51
#
#-------------------------------------------------

QT       += core gui quick
QT       += sql
QT       += core gui
QT       += charts
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Fenetres
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    poubelle.cpp \
    choix.cpp \
    passage.cpp \
    candelabre.cpp \
    choixobjet.cpp \
    employee.cpp \
    abribus.cpp \
    poteau.cpp \
    db.cpp \
    notification.cpp

HEADERS  += mainwindow.h \
    choix.h \
    passage.h \
    candelabre.h \
    choixobjet.h \
    employee.h \
    abribus.h \
    poteau.h \
    poubelle.h \
    db.h \
    notification.h

FORMS    += mainwindow.ui \
    poubelle.ui \
    choix.ui \
    passage.ui \
    candelabre.ui \
    choixobjet.ui \
    employee.ui \
    abribus.ui \
    poteau.ui \
    notification.ui \
    arduino.ui

RESOURCES += \
    ressource.qrc

DISTFILES += \
    ../ressource/crosswalk.gif \
    ../ressource/abribus.jpg \
    ../ressource/auto_opening trash.jpg \
    ../ressource/capteur de poids.jpg \
    ../ressource/crosswalk eclairé.jpg \
    ../ressource/HTB1Jrn6GVXXXXaPXFXXq6xXFXXX6.jpg \
    ../ressource/poubelle.jpg \
    ../ressource/smart Lamp details.jpg \
    ../ressource/smart-trash-collection.jpg \
    ../ressource/garbage.png \
    ../ressource/lamp.png \
    ../ressource/led-rue-lumi-re-ext-rieure-lampe-de-route-ConvertImage.png \
    ../ressource/poteau exemple.png \
    ../ressource/poteau.png \
    ../ressource/stat.png \
    ../ressource/statt.png \
    ../icone/user-interface-elements/browser-35.png \
    ../icone/user-interface-elements/browser-30.png \
    ../icone/man.png
