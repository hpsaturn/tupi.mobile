#ifndef TUPCOLORWIDGET_H
#define TUPCOLORWIDGET_H

#include <QBrush>
#include <QSize>
#include <QPaintEvent>
#include <QWidget>

class TupColorWidget : public QWidget
{
    Q_OBJECT

    public:
        TupColorWidget();
        ~TupColorWidget();
        void setBrush(const QBrush &brush);
        QSize sizeHint() const;
        QColor color();

    protected:
        void paintEvent(QPaintEvent *painter);
        void mousePressEvent(QMouseEvent *event);

    signals:
        void clicked();        

    private:
        struct Private;
        Private *const k;

};

#endif
