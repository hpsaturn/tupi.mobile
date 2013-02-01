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

#ifndef TUPPAINTAREABASE_H
#define TUPPAINTAREABASE_H

#include <QGraphicsView>
#include <QGraphicsScene> 

#include "tupgraphicalgorithm.h"
#include "tupframe.h"

class TupCanvas : public QGraphicsView
{
    Q_OBJECT

    public:
        TupCanvas(QGraphicsScene *scene, const QPen pen, double opacity, QWidget *parent);
        ~TupCanvas();
        TupFrame * frame();
        void updatePenSize(int width);
        void updatePenColor(const QColor color);
        void updatePenOpacity(double opacity);
        void updatePenBrush(Qt::BrushStyle brushStyle);

        void undo();
        void redo();
        void clear();
        bool isEmpty();

    protected:
        virtual void drawBackground(QPainter *painter, const QRectF &rect);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        // bool event(QEvent *event);

    private:
        void smoothPath(QPainterPath &path, double smoothness, int from = 0, int to = -1);
        int alphaValue(double opacity);

        struct Private;
        Private *const k;
};

#endif
