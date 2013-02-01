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

#include "tupframe.h"
#include "tuppathitem.h"

#include <QHash>
#include <QTextStream>
#include <QDebug>

struct TupFrame::Private
{
    QHash<int, TupPathItem *> graphics;
};

TupFrame::TupFrame() : QObject(), k(new Private)
{
}

TupFrame::~TupFrame()
{
}

QDomElement TupFrame::toXml(QDomDocument &doc) const
{
    QDomElement root = doc.createElement("frame");
    doc.appendChild(root);

    QHashIterator<int, TupPathItem *> i(k->graphics);
    while (i.hasNext()) {
           i.next();
           QDomElement object = doc.createElement("object");
           TupPathItem *item = (TupPathItem *) i.value();
           object.appendChild(item->toXml(doc));
           root.appendChild(object);
    }

    return root;
}

void TupFrame::addItem(TupPathItem *item)
{
    int index = k->graphics.size();
    k->graphics.insert(index, item);

    QDomDocument doc;
    QDomElement xml = item->toXml(doc);
    QString newDoc;
    QTextStream text(&newDoc);
    text << xml;

#ifdef TUP_DEBUG
    qDebug() << "TupFrame::addItem() - Object:";
    qDebug() << newDoc;
#endif
}

TupPathItem * TupFrame::takeItem(int index)
{
    TupPathItem *item = (TupPathItem *) k->graphics.take(index);
    return item;
}

void TupFrame::clear()
{
    k->graphics.clear();
}

int TupFrame::count()
{
    return k->graphics.size();
}
