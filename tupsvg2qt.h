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

#ifndef TUPSVG2QT_H
#define TUPSVG2QT_H

#include <QString>
#include <QPainterPath>
#include <QPen>
#include <QXmlAttributes>
#include <QBrush>

class TupSvg2Qt
{
    private:
        TupSvg2Qt();
        ~TupSvg2Qt();
        
    public:
        static bool svgpath2qtpath(const QString &data, QPainterPath &path);
        static bool svgmatrix2qtmatrix(const QString &data, QMatrix &matrix);
        static bool parsePointF(const QString &pointstr, QPointF &point);
        
        static void parsePen(QPen &pen, const QXmlAttributes &attributes);
        static bool parseBrush(QBrush &brush, const QXmlAttributes &attributes);
        
        static QList<qreal> parseNumbersList(QString::const_iterator &itr);
};

#endif
