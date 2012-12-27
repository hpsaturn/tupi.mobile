#include "tupbrushmanager.h"

struct TupBrushManager::Private
{
    Private() : pen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap)), brush(Qt::transparent) {}
    QPen pen;
    QBrush brush;
};

TupBrushManager::TupBrushManager(QObject * parent) : QObject(parent), k(new Private)
{
}

TupBrushManager::TupBrushManager(const QPen &pen, const QBrush &brush, QObject * parent) : QObject(parent), k(new Private)
{
    k->pen = pen;
    k->brush = brush;
}

TupBrushManager::~TupBrushManager()
{
    delete k;
}

void TupBrushManager::setPen(const QPen &pen)
{
    k->pen = pen;
    emit penChanged(k->pen);
}

void TupBrushManager::setPenColor(const QColor &color)
{
    QBrush brush = k->pen.brush();
    brush.setColor(color);
    k->pen.setBrush(brush);

    emit penChanged(k->pen);
}

void TupBrushManager::setPenSize(int size)
{
    k->pen.setWidth(size);
}

QPen TupBrushManager::pen() const
{
    return k->pen;
}

void TupBrushManager::setBrush(const QBrush &brush)
{
    k->brush = brush;
    emit brushChanged(brush);
}

QBrush TupBrushManager::brush() const
{
    return k->brush;
}

int TupBrushManager::penWidth() const
{
    return k->pen.width();
}

QColor TupBrushManager::penColor() const
{
    return k->pen.color();
}

QBrush TupBrushManager::penBrush() const
{
    return k->pen.brush();
}

QBrush TupBrushManager::brushColor() const
{
    return k->brush.color();
}
