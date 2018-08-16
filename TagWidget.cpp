#include "TagWidget.h"

TagWidget::TagWidget(const QString &word, QWidget *parent) :
    mWord(word),QWidget(parent)
{

    mFont = QFont();

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);




}

void TagWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setFont(mFont);


    painter.drawRoundRect(rect());
    painter.drawText(rect(), mWord);





    QWidget::paintEvent(event);
}

QSize TagWidget::sizeHint() const
{
    return wordSize() + QSize(10,10);
}

QSize TagWidget::wordSize() const
{
    QFontMetrics metrics(mFont);

    return QSize(metrics.width(mWord), metrics.height());

}
