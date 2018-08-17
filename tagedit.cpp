#include "tagedit.h"

TagEdit::TagEdit(QWidget *parent) : QWidget(parent)
{

    mLayout = new FlowLayout;
    setLayout(mLayout);

    QPalette pal = palette();
    pal.setBrush(QPalette::Background, Qt::white);

    setPalette(pal);

}

void TagEdit::addTag(const QString &name)
{
    addTag(new TagItem(name));
}

void TagEdit::addTag(TagItem *item)
{

    mItems.append(item);
    mLayout->addWidget(item);

    connect(item, &TagItem::closed,[this,item]()
    {
        mItems.removeOne(item);
        delete item;

    });

}

void TagEdit::mousePressEvent(QMouseEvent *event)
{

    for (auto * item : mItems)
    {

        QRect r = QRect(item->pos().x(), item->pos().y(), item->rect().width(), item->rect().height());

        if (r.contains(event->pos()))
        {
            QToolTip::showText(event->globalPos(), "salut", this);

        }

    }



    QWidget::mousePressEvent(event);
}
