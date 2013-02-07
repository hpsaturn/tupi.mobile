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

TupColorSlider::TupColorSlider(const QColor& start, const QColor& end, QWidget *parent) :
    QGraphicsView(parent),
    start_color(start),
    end_color(end),
    value(0)
{
    img = new QImage(QString(":/images/tip.png"));

    setUpdatesEnabled(true);
}

TupColorSlider::~TupColorSlider()
{
    delete img;
}

void
TupColorSlider::setRange(int n, int x)
{
    min=n;
    max=x;
}

void
TupColorSlider::setColors(const QColor& start, const QColor& end)
{
    start_color=start;
    end_color=end;
    this->update();
}

void
TupColorSlider::mousePressEvent ( QMouseEvent * event )
{
}

void
TupColorSlider::mouseMoveEvent ( QMouseEvent * event )
{
    value = event->y();

    if(value > viewport()->height())
        value = viewport()->height();

    if(value<0)
        value=0;

    int r = min + (max-min)*(1.0 - float(event->y())/float(viewport()->height()));

    qDebug() << "mouseMoveEvent =  " << r << " " <<  float(event->y())/float(viewport()->height());

    this->update();

    emit valueChanged(r);
}

void
TupColorSlider::paintScales()
{
    QPainter qp(viewport());

    int N=32;
    int H=viewport()->height()/(N-1);

    int sr=0;
    int sg=0;
    int sb=0;
    for(int x=0; x<=N; x++)
    {
        QColor color;
        int r,g,b;
        r = x*(end_color.red() - start_color.red())/N + start_color.red();
        g = x*(end_color.green() - start_color.green())/N + start_color.green();
        b = x*(end_color.blue() - start_color.blue())/N + start_color.blue();

        sr += r;
        sg += g;
        sb += b;

        color.setRed( r );
        color.setGreen( g );
        color.setBlue( b );

        qp.setPen(color);
        qp.setBrush(color);
        qp.drawRect(0,x*H,viewport()->width(), H);
    }

    qp.drawImage(viewport()->width()/2-img->size().width()/2,value,*img);
}

void
TupColorSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    paintScales();
}
