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

#ifndef TUPMAINWINDOW_H
#define TUPMAINWINDOW_H

#include <QMainWindow>

class TupMainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        TupMainWindow();
        ~TupMainWindow(); 

    protected:
        void closeEvent(QCloseEvent *event);
        void resizeEvent(QResizeEvent *event);

    private:
        void setBrushesGrid();
        void setToolBar();
        void setCanvas();

        struct Private;
        Private *const k;

    private slots:
        void postIt();
        void setMetadata();
        void shareURL(const QString &url);
        void showDialog();
        void penStrokeSizeDialog();
        void colorDialog();
        void opacityDialog();
        void brushDialog();

        void updatePenStrokeSize(int size);
        void updatePenColor(const QColor color);
        void updatePenOpacity(double opacity);
        void updatePenBrush(Qt::BrushStyle style);

        void undo();
        void redo();
        void newCanvas();
        void showAbout();
};

#endif
