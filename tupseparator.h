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

#ifndef TUPSEPARATOR_H
#define TUPSEPARATOR_H

#include <QFrame>

/**
 * Standard horizontal or vertical separator.
 *
 * @author Michael Roth \<mroth@wirlweb.de\>
 */

class TupSeparator : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation);

    public:

    /**
     * Constructor.
     * @param parent parent object.
     * @param f extra QWidget flags.
     **/
    TupSeparator(QWidget* parent=0);

    /**
     * Constructor.
     * @param orientation Set the orientation of the separator.
     * Possible values are Horizontal or Vertical.
     * @param parent parent object.
     * @param f extra QWidget flags.
     **/
    TupSeparator(Qt::Orientation orientation, QWidget* parent=0);

    /**
     * Returns the orientation of the separator.
     * @return int Possible values Horizontal or Vertical.
     **/
     Qt::Orientation orientation() const;

    /**
     * Set the orientation of the separator to @p orientation
     *
     * @param orientation Possible values are Vertical and Horizontal.
     */
     void setOrientation(Qt::Orientation orientation);

    protected:
        virtual void virtual_hook(int id, void* data);

    private:
        class TupSeparatorPrivate* k;
};

#endif // TSEPARATOR_H
