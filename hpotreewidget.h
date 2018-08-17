#ifndef HPOTREEWIDGET_H
#define HPOTREEWIDGET_H

#include <QtWidgets>
#include "hpomodel.h"
#include "qfonticon.h"

class HpoTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HpoTreeWidget(QWidget *parent = nullptr);



    void contextMenuEvent(QContextMenuEvent * event) override;

public Q_SLOTS:
    void setRoot(Node * node );
    void search(const QString& search);



private:
    QTreeView * mView;
    HpoModel * mModel;
    QLineEdit * mSearchEdit;
    QToolBar * mToolBar;
    QAction * mrootAction;


};

#endif // HPOTREEWIDGET_H
