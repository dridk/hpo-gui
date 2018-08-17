#include "mainwindow.h"
#include <QApplication>

#include "flowlayout.h"
#include <QtWidgets>
#include "tagitem.h"
#include "qfonticon/qfonticon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    QFontIcon::addFont(":/materialdesignicons-webfont.ttf");

    QWidget * w = new QWidget;
    FlowLayout * l = new FlowLayout;

    w->setStyleSheet("background-color:white;");

    l->addWidget(new TagItem("HPO:424242"));

    l->addWidget(new TagItem("salut"));

    w->setLayout(l);

    w->show();


    return a.exec();
}
