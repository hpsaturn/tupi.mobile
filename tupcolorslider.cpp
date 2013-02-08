/***************************************************************************
 *   Project TUPI: Open 2D Magic                                           *
 *   Component: tupi.mobile                                                *
 *   Project Contact: info@maefloresta.com                                 *
 *   Project Website: http://www.maefloresta.com                           *
 *                                                                         *
 *   Developers:                                                           *
 *   2012:                                                                 *
 *    Gustavo Gonzalez / @xtingray                                         *
 *    Andres Calderon / @andresfcalderon                                   *
 *    Antonio Vanegas / @hpsaturn                                          *
 *                                                                         *
 *   Tupi is a fork of the KTooN project                                   *
 *   KTooN's versions:                                                     *
 *   2006:                                                                 *
 *    David Cuadrado                                                       *
 *    Jorge Cuadrado                                                       *
 *   2003:                                                                 *
 *    Fernado Roldan                                                       *
 *    Simena Dinas                                                         *
 *                                                                         *
 *   Copyright (C) 2012 Mae Floresta - http://www.maefloresta.com          *
 *   License:                                                              *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include "tupcolorslider.h"

#include <QDebug>

struct TupColorSlider::Private
{
    int min;
    int max;
    QColor startColor;
    QColor endColor;
    QImage *image;
    int value;
    Qt::Orientation orientation;
};

TupColorSlider::TupColorSlider(Qt::Orientation orientation, const QColor &start, const QColor &end, QWidget *parent) : QGraphicsView(parent), k(new Private)
{
    k->orientation = orientation; 
    k->startColor = start;
    k->endColor = end;
    k->value = 0;

    if (k->orientation == Qt::Vertical)
        k->image = new QImage(QString(":/images/tip_v.png"));
    else 
        k->image = new QImage(QString(":/images/tip_h.png"));

    setUpdatesEnabled(true);
}

TupColorSlider::~TupColorSlider()
{
}

void TupColorSlider::setRange(int min, int max)
{
    k->min = min;
    k->max = max;
}

void TupColorSlider::setValue(int value)
{
    if (k->orientation == Qt::Vertical) {
        k->value = viewport()->height()*value/255; 
        if (value == 255)
            k->value = k->value - k->image->size().height();
    } else {
        k->value = viewport()->width()*value/255; 
        if (value == 255)
            k->value = k->value - k->image->size().width();
    }

    this->update();
}

void TupColorSlider::setColors(const QColor &start, const QColor &end)
{
    k->startColor = start;
    k->endColor = end;
    this->update();
}

void TupColorSlider::mousePressEvent(QMouseEvent *event)
{
    int pos = -1;
    if (k->orientation == Qt::Vertical)
        pos = event->y();
    else
        pos = event->x();

    calculateColorIndex(pos);
}

void TupColorSlider::mouseMoveEvent(QMouseEvent *event)
{
    int pos = -1;
    if (k->orientation == Qt::Vertical) 
        pos = event->y();
    else
        pos = event->x();

    calculateColorIndex(pos);
}

void TupColorSlider::calculateColorIndex(int pos)
{
    int length = -1;

    if (k->orientation == Qt::Vertical) {
        length = viewport()->height();
        k->value = pos;
        if (pos > (length - k->image->size().height())) {
            k->value = length - k->image->size().height();
            this->update();
            emit valueChanged(255);
            return;
        }
    } else {
        length = viewport()->width();
        if (pos > (length - k->image->size().width())) {
            k->value = length - k->image->size().width();
            this->update();
            emit valueChanged(255);
            return;
        }
        k->value = pos;
    }

    int value = -1;
    if (k->orientation == Qt::Vertical) 
        value = k->min + (k->max - k->min) * (1.0 - float(pos)/float(length));
    else 
        value = k->min + (k->max - k->min) * (float(pos)/float(length));

#ifdef TUP_DEBUG
       qDebug() << "mouseMoveEvent =  " << value << " - " <<  float(pos)/float(length);
#endif

    if (k->value < 0)
        k->value = 0;

    if (value < 0)
        value = 0;

    this->update();
    emit valueChanged(value);
}

void TupColorSlider::paintScales()
{
    QPainter painter(viewport());
    int segments = 32;
    int length = -1;

    if (k->orientation == Qt::Vertical)
        length = viewport()->height();
    else
        length = viewport()->width();

    int delta = length/(segments-1);
    for (int section=0; section<=segments; section++) {
         QColor color;
         int r;
         int g;
         int b;
         r = section*(k->endColor.red() - k->startColor.red()) / segments + k->startColor.red();
         g = section*(k->endColor.green() - k->startColor.green()) / segments + k->startColor.green();
         b = section*(k->endColor.blue() - k->startColor.blue()) / segments + k->startColor.blue();

         if ((r > -1 && r < 256) && (g > -1 && g < 256) && (b > -1 && b < 256)) {
             color.setRed(r);
             color.setGreen(g);
             color.setBlue(b);

             painter.setPen(color);
             painter.setBrush(color);
             if (k->orientation == Qt::Vertical) {
                 int width = viewport()->width();
                 int imageW = k->image->size().width()-16;
                 painter.drawRect((width - imageW)/2, section*delta, imageW, delta);
             } else {
                 int height = viewport()->height();
                 int imageH = k->image->size().height()-16;
                 painter.drawRect(section*delta, (height - imageH)/2, delta, imageH);
             }
         }
    }

    if (k->orientation == Qt::Vertical) {
        int width = viewport()->width();
        int imageW = k->image->size().width();
        painter.drawImage((width/2)-(imageW/2), k->value, *k->image);
    } else {
        int height = viewport()->height();
        int imageH = k->image->size().height();
        painter.drawImage(k->value, (height/2)-(imageH/2), *k->image);
    }
}

void TupColorSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paintScales();
}
