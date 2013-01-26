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

#include "tuppalettedialog.h"
#include "tupcolorwidget.h"

#include <cmath>
#include <QBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QDebug>

struct TupPaletteDialog::Private
{
    QVBoxLayout *innerLayout;
    QList<TupColorWidget *> colors;
    int currentColorIndex;
    QBrush brush;
    QColor color;
    QSize size;
};

TupPaletteDialog::TupPaletteDialog(const QBrush brush, const QSize size, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("* { background-color: rgb(232,232,232) }");

    k->brush = brush;
    k->size = size;
    k->currentColorIndex = -1;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(10);

    k->innerLayout = new QVBoxLayout;

    setColorsArray();

    QPixmap pixmap(":images/close.png");
    QIcon buttonIcon(pixmap);
    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(buttonIcon);
    closeButton->setIconSize(pixmap.rect().size());
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton(closeButton, QDialogButtonBox::ActionRole);

    k->innerLayout->addSpacing(10);
    k->innerLayout->addWidget(buttonBox);

    layout->addLayout(k->innerLayout);
}

TupPaletteDialog::~TupPaletteDialog()
{
}

void TupPaletteDialog::setColorsArray()
{
    /* SQA: Enhanced code under development
    int w = k->size.width();
    int h = k->size.height();
    int rows = w / 100;
    int columns =  h / 50;
    int deltaX = 255/rows;
    int deltaY = 255/columns;

    qDebug() << "rows: " << rows;
    qDebug() << "columns: " << columns;
    qDebug() << "deltaX: " << deltaX;
    qDebug() << "deltaY: " << deltaY;

    int r = 0;
    int g = 0;
    int b = 0;
    int deltaXY = 0;
    int index = 0;
    for (int i=0; i<rows; i++) {
         QBoxLayout *matrix = new QHBoxLayout;
         matrix->setSpacing(10);
         for (int j=0; j<columns; j++) {
              r = (i*deltaX);    
              g = (j*deltaY); 
              deltaXY += qrand() % (5 + 1);
              b = deltaXY;

              qDebug() << "[" << i << ", " << j << "] -> (" << r << ", " << g << ", " << b << ")";
              if (r > 255)
                  r = 255;
              if (g > 255)
                  g = 255;
              if (b > 255)
                  b = 255;
              QColor color(r, g, b);
              QBrush brush(color, k->brush.style());
              TupColorWidget *button = new TupColorWidget(index, brush);
              connect(button, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
              index++;
              k->colors << button;
              matrix->addWidget(button);
         }

         k->innerLayout->addLayout(matrix);
    }
    */

    int w = k->size.width();
    int h = k->size.height();
    int rows = w / 100;
    int columns =  h / 50;

    int index = 0;
    for (int j=0; j<rows; j++) {
         QBoxLayout *matrix = new QHBoxLayout;
         matrix->setSpacing(10);

         for (int i=0; i<columns; i++) {
              int r = qrand() % (255 + 1);
              int g = qrand() % (255 + 1);
              int b = qrand() % (255 + 1);

              QColor color(r, g, b);
              QBrush brush(color, k->brush.style());
              TupColorWidget *button = new TupColorWidget(index, brush);
              connect(button, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
              index++;
              k->colors << button;
              matrix->addWidget(button);
         }

         k->innerLayout->addLayout(matrix);
    }
}

void TupPaletteDialog::updateMatrix(int index)
{
    if (index != k->currentColorIndex) {
        if (k->currentColorIndex >= 0) {
            TupColorWidget *button = (TupColorWidget *) k->colors.at(k->currentColorIndex);
            button->unselect();
        }
        TupColorWidget *selection = (TupColorWidget *) k->colors.at(index);
        k->color = selection->color();
        k->currentColorIndex = index;
    }
}

void TupPaletteDialog::closeDialog()
{
    emit updateColor(k->color);
    close();
}
