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

#ifndef TUPSERIALIZER_H
#define TUPSERIALIZER_H

#include <QDomDocument>
#include <QDomElement>
#include <QXmlAttributes>
#include <QBrush>
#include <QPen>

class QGraphicsItem;

class TupSerializer
{
    public:
        TupSerializer();
        ~TupSerializer();
        
        static QDomElement properties(const QGraphicsItem *item, QDomDocument &doc);
        static void loadProperties(QGraphicsItem *item, const QXmlAttributes &atts);
        static void loadProperties(QGraphicsItem *item, const QDomElement &e);
        
        static QDomElement gradient(const QGradient *gradient, QDomDocument &doc);
        static QGradient * createGradient(const QXmlAttributes &atts);
        
        static QDomElement brush(const QBrush *brush, QDomDocument &doc);
        static void loadBrush(QBrush &brush, const QXmlAttributes &atts);
        static void loadBrush(QBrush &brush, const QDomElement &e);
        
        static QDomElement pen(const QPen *pen, QDomDocument &doc);
        static void loadPen(QPen &pen, const QXmlAttributes &atts);
        static void loadPen(QPen &pen, const QDomElement &e);
        
        static QDomElement font(const QFont *font, QDomDocument &doc);
        static void loadFont(QFont &font, const QDomElement &e);
        static void loadFont(QFont &font, const QXmlAttributes &atts);
};        

#endif
