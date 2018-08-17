#include "hpotreewidget.h"

HpoTreeWidget::HpoTreeWidget(QWidget *parent) : QWidget(parent)
{

    setWindowTitle("HPO Tree");

    mView       = new QTreeView;
    mModel      = new HpoModel;
    mSearchEdit = new QLineEdit;
    mToolBar    = new QToolBar;

    mModel->setDatabase("/data/hpo.db");
    mView->setModel(mModel);
    mView->header()->hide();


    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setSpacing(1);

    vLayout->addWidget(mToolBar);
    vLayout->addWidget(mView);
    vLayout->addWidget(mSearchEdit);


    setLayout(vLayout);

    //mToolBar->setIconSize(QSize(16,16));
    mToolBar->addAction(FIcon(0xf142),"");
    mrootAction = mToolBar->addAction("Root");

    QAction * searchAction = new QAction(FIcon(0xf349),QString());
    searchAction->setMenu(new QMenu());
    searchAction->menu()->addAction("by HPO");
    searchAction->menu()->addAction("by term");
    mSearchEdit->addAction(searchAction,QLineEdit::LeadingPosition);

    connect(mSearchEdit, &QLineEdit::returnPressed, [this](){

        search(mSearchEdit->text());

    });

    mView->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);

    setRoot(new Node());


}

void HpoTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{

    QMenu menu(this);

   QModelIndex index =  mView->currentIndex();

   if (index.isValid())
   {

       Node * node = mModel->nodeFromIndex(mModel->index(index.row(),0,index.parent()));


       menu.addAction("Set as root");
       menu.addSection("parent");


       qDebug()<<"test";

       for (Node * n : node->allParents()){
           QAction * action = menu.addAction(QString("%1 %2").arg(n->hpo()).arg(n->name()),[this,n](){

               setRoot(n);

           });


       }

   }

    menu.exec(event->globalPos());


}

void HpoTreeWidget::setRoot(Node* node)
{
    mModel->setRoot(node);
    mrootAction->setText(mModel->rootNode()->name());

}

void HpoTreeWidget::search(const QString &search)
{
    mModel->search(search);
}
