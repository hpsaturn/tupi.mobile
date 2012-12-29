#include "tupcolorwidget.h"
#include <QPainter>

struct TupColorWidget::Private
{
    QBrush brush;
};

TupColorWidget::TupColorWidget() : k(new Private)
{
}

TupColorWidget::~TupColorWidget()
{
}

QSize TupColorWidget::sizeHint() const 
{
    QSize size(20, 20);
    return size;
}

void TupColorWidget::setBrush(const QBrush &brush)
{
    k->brush = brush;
    update();
}

void TupColorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), k->brush);
}

void TupColorWidget::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

QColor TupColorWidget::color()
{
    return k->brush.color();
}
