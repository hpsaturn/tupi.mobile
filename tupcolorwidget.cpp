#include "tupcolorwidget.h"
#include <QPainter>

struct TupColorWidget::Private
{
    QBrush brush;
    int index;
    bool selected;
};

TupColorWidget::TupColorWidget(int index, const QBrush &brush) : k(new Private)
{
    k->index = index;
    k->selected = false;
    k->brush = brush;
}

TupColorWidget::~TupColorWidget()
{
}

QSize TupColorWidget::sizeHint() const 
{
    return QSize(50, 50);
}

void TupColorWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), k->brush);
    if (k->selected) {
        QRect border = rect();
        painter.setPen(QPen(QColor(200, 200, 200), 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(border);
        painter.setPen(QPen(QColor(150, 150, 150), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(border);
    }
}

void TupColorWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    k->selected = true;
    emit clicked(k->index);
    update();
}

QColor TupColorWidget::color()
{
    return k->brush.color();
}

void TupColorWidget::unselect()
{
    k->selected = false;
    update();
}
