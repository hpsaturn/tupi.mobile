#include "tuppenpreviewcanvas.h"

struct TupPenPreviewCanvas::Private
{
    int width;
    double opacity;
    QColor color;
    Qt::BrushStyle style;
};

TupPenPreviewCanvas::TupPenPreviewCanvas(QPen pen, double opacity, QWidget *parent) : QWidget(parent), k(new Private)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    k->width = pen.width();
    k->color = pen.color();
    k->opacity = opacity;
    k->style = pen.brush().style();
}

TupPenPreviewCanvas::~TupPenPreviewCanvas()
{
}

void TupPenPreviewCanvas::render(int width)
{
    k->width = width;
    update();
}

void TupPenPreviewCanvas::render(double opacity)
{
    k->opacity = opacity;
    update();
}

QSize TupPenPreviewCanvas::minimumSizeHint() const
{
    return QSize(100, 106);
}

QSize TupPenPreviewCanvas::sizeHint() const
{
    return QSize(100, 106);
}

void TupPenPreviewCanvas::paintEvent(QPaintEvent *)
{
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.fillRect(0, 0, width(), height(), QColor(255, 255, 255));

     QPen border(QColor(0, 0, 0));
     border.setWidth(0.5);
     painter.setPen(border);
     painter.drawRect(0, 0, width(), height());

     painter.translate(width() / 2, height() / 2);

     QBrush brush;
     brush = QBrush(k->color, k->style);

     QPen pen(Qt::NoPen);
     painter.setPen(pen);
     painter.setBrush(brush);
     painter.setOpacity(k->opacity);
     painter.drawEllipse(-(k->width/2), -(k->width/2), k->width, k->width);
}
