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

#include "tupseparator.h"
#include <QStyleOption>
#include <QPainter>

TupSeparator::TupSeparator(QWidget* parent) : QFrame(parent)
{
   setLineWidth(1);
   setMidLineWidth(0);
   setOrientation(Qt::Horizontal);
}

TupSeparator::TupSeparator(Qt::Orientation orientation, QWidget* parent) : QFrame(parent)
{
   setLineWidth(1);
   setMidLineWidth(0);
   setOrientation(orientation);
}

void TupSeparator::setOrientation(Qt::Orientation orientation)
{
   if (orientation == Qt::Vertical) {
      setFrameShape(QFrame::VLine);
      setFrameShadow(QFrame::Sunken);
      setMinimumSize(2, 0);
   } else {
      setFrameShape(QFrame::HLine);
      setFrameShadow(QFrame::Sunken);
      setMinimumSize(0, 2);
   }
}

Qt::Orientation TupSeparator::orientation() const
{
   return (frameStyle() & VLine) ? Qt::Vertical : Qt::Horizontal;
}

void TupSeparator::virtual_hook(int, void*)
{ 
    /*BASE::virtual_hook( id, data );*/ 
}
