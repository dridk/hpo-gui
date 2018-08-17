#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{



    mHpoTreeWidget= new HpoTreeWidget();



    QDockWidget * hpoDockWidget = new QDockWidget;
    hpoDockWidget->setWidget(mHpoTreeWidget);
    addDockWidget(Qt::LeftDockWidgetArea, hpoDockWidget);
    hpoDockWidget->setWindowTitle(mHpoTreeWidget->windowTitle());



    //    ui->treeView->setModel(mModel);
    //    ui->geneView->setModel(mGeneModel);
    //   // ui->treeView->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);


    //    connect(ui->lineEdit, &QLineEdit::returnPressed, [this](){

    //        mModel->load(ui->lineEdit->text());

    //    });


    //    connect(ui->treeView, &QTreeView::doubleClicked,[this](const QModelIndex& index){

    //     QModelIndex i = mModel->index(index.row(),0, index.parent());
    //     ui->lineEdit_2->setText(ui->lineEdit_2->text()+" "+mModel->data(i, Qt::DisplayRole).toString());

    //    });

    //    connect(ui->lineEdit_2, &QLineEdit::returnPressed, [this](){

    //        qDebug()<<"Load gene";
    //        mGeneModel->load(ui->lineEdit_2->text());

    //    });

}

MainWindow::~MainWindow()
{
    //  delete ui;
}
