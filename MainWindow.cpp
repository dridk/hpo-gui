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
   // ui->treeView->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);


    connect(ui->lineEdit, &QLineEdit::returnPressed, [this](){

        mModel->load(ui->lineEdit->text());

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
