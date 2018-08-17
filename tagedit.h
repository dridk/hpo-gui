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

    void addTag(const QString& name);
    void addTag(TagItem * item);

    void mousePressEvent(QMouseEvent * event);



private:
    FlowLayout * mLayout;

    QList<TagItem*> mItems;

};

#endif // TAGEDIT_H
