#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new HpoModel();

    mModel->setDatabase("/data/hpo.db");


    ui->treeView->setModel(mModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}
