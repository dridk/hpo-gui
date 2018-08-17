#ifndef TAGWIDGET_H
#define TAGWIDGET_H
#include <QtWidgets>
#include <QPainter>
#include "qfonticon/qfonticon.h"

class TagItem : public QWidget
{
    Q_OBJECT
public:
    explicit TagItem(const QString& word, QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent * event) override;
    QSize sizeHint() const override;

        QSize wordSize() const;

        void mouseMoveEvent(QMouseEvent * event);
        void mousePressEvent(QMouseEvent * event);
        void enterEvent(QEvent * event);
        void leaveEvent(QEvent *event);


private:
    QString mWord;
    QFont mFont;

    bool mHover = false;


};

#endif // TAGWIDGET_H
