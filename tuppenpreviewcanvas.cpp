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
