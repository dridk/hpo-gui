#include "mainwindow.h"
#include <QApplication>

#include "flowlayout.h"
#include <QtWidgets>
#include "tagedit.h"
#include "qfonticon/qfonticon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    QFontIcon::addFont(":/materialdesignicons-webfont.ttf");



    TagEdit * edit = new TagEdit;

    edit->addTag("sacha");
    edit->addTag("sacha");
    edit->addTag("sacha");
    edit->addTag("sacha");


    edit->show();


    return a.exec();
}
