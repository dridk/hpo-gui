#include "tagitem.h"

TagItem::TagItem(const QString &word, QWidget *parent) :
    mWord(word),QWidget(parent)
{

    mFont = QFont();

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    setMouseTracking(true);

}

void TagItem::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setFont(mFont);

   // painter.setRenderHint(QPainter::Antialiasing,true);


    QRect roundRect = rect().adjusted(4,4,-4,-4);


    painter.setBrush(QColor("#E0EAF1"));


    painter.setPen(Qt::NoPen);

    painter.drawRect(roundRect);

    painter.setPen(QColor("#80A3BB"));

    QIcon crossIcon = FIconColor(0xf156, mHover ? Qt::red : painter.pen().color());
    painter.drawPixmap(rect().right() - 20 , rect().center().y()-7, crossIcon.pixmap(16,16));

    painter.drawText(roundRect.adjusted(-10,0,0,0), Qt::AlignCenter, mWord);





    QWidget::paintEvent(event);
}

QSize TagItem::sizeHint() const
{
    return wordSize() + QSize(40,15);
}

QSize TagItem::wordSize() const
{
    QFontMetrics metrics(mFont);

    return QSize(metrics.width(mWord), metrics.height());

}

void TagItem::mouseMoveEvent(QMouseEvent *event)
{

    QWidget::mouseMoveEvent(event);
}

void TagItem::mousePressEvent(QMouseEvent *event)
{
    if (event->pos().x() > rect().width() - 20 )
        qDebug()<<"close";


    QWidget::mousePressEvent(event);
}

void TagItem::enterEvent(QEvent *event)
{
    mHover = true;
    update();

}

void TagItem::leaveEvent(QEvent *event)
{
    mHover = false;
    update();
}
