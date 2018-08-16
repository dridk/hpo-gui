#include "MainWindow.h"
#include <QApplication>

#include "flowlayout.h"
#include <QtWidgets>
#include "TagWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    QWidget * w = new QWidget;
    FlowLayout * l = new FlowLayout;

    l->addWidget(new TagWidget("salut"));

    l->addWidget(new TagWidget("salut"));

    w->setLayout(l);

    w->show();


    return a.exec();
}
