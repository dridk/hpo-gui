#ifndef TAGWIDGET_H
#define TAGWIDGET_H
#include <QWidget>
#include <QPainter>
class TagWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TagWidget(const QString& word, QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent * event) override;
    QSize sizeHint() const override;

        QSize wordSize() const;


private:
    QString mWord;
    QFont mFont;


};

#endif // TAGWIDGET_H
