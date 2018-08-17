#ifndef TAGEDIT_H
#define TAGEDIT_H

#include <QWidget>
#include "flowlayout.h"
#include"tagitem.h"

class TagEdit : public QWidget
{
    Q_OBJECT
public:
    explicit TagEdit(QWidget *parent = nullptr);



private:
    FlowLayout * mLayout;

};

#endif // TAGEDIT_H
