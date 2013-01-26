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
        painter.setPen(QPen(QColor(190, 190, 190), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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
