#include "tuppenthicknesswidget.h"

struct TupPenThicknessWidget::Private
{
    int thickness;
    double opacity;
    int brush;
    QColor color;
    QBrush currentBrush;
};

TupPenThicknessWidget::TupPenThicknessWidget(QWidget *parent) : QWidget(parent), k(new Private)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    k->opacity = 1.0;
    k->thickness = 100;
}

TupPenThicknessWidget::~TupPenThicknessWidget()
{
}

void TupPenThicknessWidget::render(int thickness)
{
    k->thickness = thickness;
    update();
}

void TupPenThicknessWidget::render(double opacity)
{
    k->opacity = opacity;
    update();
}

void TupPenThicknessWidget::setColor(const QColor color)
{
    k->color = color;
}

void TupPenThicknessWidget::setBrush(int index)
{
    k->brush = index;
    update();
}

void TupPenThicknessWidget::setBrush(const QBrush brush)
{
    k->currentBrush = brush;
    k->brush = -1;
}

QSize TupPenThicknessWidget::minimumSizeHint() const
{
    return QSize(100, 106);
}

QSize TupPenThicknessWidget::sizeHint() const
{
    return QSize(100, 106);
}

void TupPenThicknessWidget::paintEvent(QPaintEvent *)
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
     Qt::BrushStyle style = Qt::BrushStyle(k->brush);
     
     if (style != Qt::TexturePattern) {  
         if (k->brush != -1) {
             brush = QBrush(Qt::BrushStyle(k->brush));
             brush.setColor(k->color);
         } else {
             if (k->currentBrush.gradient())
                 brush = k->currentBrush;
         }
         QPen pen(Qt::NoPen);
         painter.setPen(pen);
         painter.setBrush(brush);
         painter.setOpacity(k->opacity);
         painter.drawEllipse(-(k->thickness/2), -(k->thickness/2), k->thickness, k->thickness);
     }
}
