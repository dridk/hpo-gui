#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hpomodel.h"
#include "genemodel.h"

#include "hpotreewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    HpoTreeWidget * mHpoTreeWidget;

};

#endif // MAINWINDOW_H
