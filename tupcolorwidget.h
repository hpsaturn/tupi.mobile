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
        TupColorWidget(int index, const QBrush &brush);
        ~TupColorWidget();
        QSize sizeHint() const;
        QColor color();
        void unselect();

    protected:
        void paintEvent(QPaintEvent *painter);
        void mousePressEvent(QMouseEvent *event);

    signals:
        void clicked(int index);        

    private:
        struct Private;
        Private *const k;

};

#endif
