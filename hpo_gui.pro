#-------------------------------------------------
#
# Project created by QtCreator 2018-08-06T12:32:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hpo_gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include("qfonticon/qfonticon.pri")

SOURCES += \
        main.cpp \
    flowlayout.cpp \
    tagitem.cpp \
    tagedit.cpp \
    node.cpp \
    mainwindow.cpp \
    hpomodel.cpp \
    genemodel.cpp \
    hpotreewidget.cpp

HEADERS += \
    flowlayout.h \
    tagitem.h \
    tagedit.h \
    node.h \
    mainwindow.h \
    hpomodel.h \
    genemodel.h \
    hpotreewidget.h

FORMS +=

RESOURCES += \
    gfx.qrc
