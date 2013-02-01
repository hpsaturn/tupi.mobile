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
    QList<TupColorWidget *> baseColors;
    int currentColorIndex;
    int currentBaseColor;
    QBrush brush;
    QColor color;
    QSize size;
    int rows;
    int columns;
};

TupPaletteDialog::TupPaletteDialog(const QBrush brush, const QSize size, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("* { background-color: rgb(232,232,232) }");

    k->brush = brush;
    k->size = size;
    k->currentColorIndex = -1;
    int w = k->size.width();
    int h = k->size.height();
    k->rows = w/100;
    k->columns = h/50;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(10);

    k->innerLayout = new QVBoxLayout;

    initColorsArray();

    QPixmap pixmap(":images/close.png");
    QIcon buttonIcon(pixmap);
    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(buttonIcon);
    closeButton->setIconSize(pixmap.rect().size());
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

    k->currentBaseColor = 0;
    QColor redColor(255, 0, 0);
    QBrush redBrush(redColor, k->brush.style());
    TupColorWidget *red = new TupColorWidget(0, redBrush);
    red->selected();
    connect(red, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << red;

    QColor greenColor(0, 255, 0);
    QBrush greenBrush(greenColor, k->brush.style());
    TupColorWidget *green = new TupColorWidget(1, greenBrush);
    connect(green, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << green;

    QColor blueColor(0, 0, 255);
    QBrush blueBrush(blueColor, k->brush.style());
    TupColorWidget *blue = new TupColorWidget(2, blueBrush);
    connect(blue, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << blue;

    QColor whiteColor(255, 255, 255);
    QBrush whiteBrush(whiteColor, k->brush.style());
    TupColorWidget *white = new TupColorWidget(3, whiteBrush);
    connect(white, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << white;

    QBoxLayout *down = new QHBoxLayout;
    down->setContentsMargins(3, 3, 3, 3);
    down->setSpacing(10);
    down->addWidget(red);
    down->addWidget(green);
    down->addWidget(blue);
    down->addWidget(white);
    down->addWidget(closeButton);

    k->innerLayout->addSpacing(10);
    k->innerLayout->addLayout(down);

    layout->addLayout(k->innerLayout);
}

TupPaletteDialog::~TupPaletteDialog()
{
}

void TupPaletteDialog::initColorsArray()
{
    int deltaX = 255/k->rows;
    int deltaY = 255/k->columns;
    int r = 255;
    int g = 0;
    int b = 0;
    int index = 0;

    for (int i=0; i < k->rows; i++) {
         QBoxLayout *matrix = new QHBoxLayout;
         matrix->setSpacing(10);
         for (int j=0; j < k->columns; j++) {
              g = (i*deltaY); 
              b = (j*deltaX);

              if (g > 255)
                  g = 255;
              if (b > 255)
                  b = 255;

              QColor cellColor(r, g, b);
              QBrush brush(cellColor, k->brush.style());
              TupColorWidget *button = new TupColorWidget(index, brush);
              connect(button, SIGNAL(clicked(int)), this, SLOT(updateSelection(int)));
              index++;
              k->colors << button;
              matrix->addWidget(button);
         }
         k->innerLayout->addLayout(matrix);
    }
}

void TupPaletteDialog::updateSelection(int index)
{
    if (index != k->currentColorIndex) {
        if (k->currentColorIndex >= 0) {
            TupColorWidget *button = (TupColorWidget *) k->colors.at(k->currentColorIndex);
            button->unselected();
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

void TupPaletteDialog::updateMatrix(int newColor)
{
    if (newColor != k->currentBaseColor) {
        k->baseColors.at(k->currentBaseColor)->unselected(); 
        k->currentBaseColor = newColor;
        int deltaX = 255 / k->rows;
        int deltaY = 255 / k->columns;

        int r = 0;
        int g = 0;
        int b = 0;
        int index = 0;
        TupPaletteDialog::Color color = TupPaletteDialog::Color(newColor);

        for (int i=0; i < k->rows; i++) {
             for (int j=0; j < k->columns; j++) {
                  switch (color) {
                          case TupPaletteDialog::Red :
                               r = 255;
                               g = (i*deltaY);
                               b = (j*deltaX);
                          break;
                          case TupPaletteDialog::Green :
                               r = (i*deltaX);
                               g = 255;
                               b = (j*deltaX);
                          break;
                          case TupPaletteDialog::Blue :
                               r = (i*deltaX);
                               g = (j*deltaY);
                               b = 255;
                          break;
                          case TupPaletteDialog::White :
                               if (j == k->columns - 1 && i == k->rows - 1) {
                                   r = 255;
                                   g = 255;
                                   b = 255;
                               } else {
                                   r = (i*deltaX);
                                   g = (i*deltaX);
                                   b = (i*deltaX);
                               }
                          break;
                  }

                  QColor cellColor(r, g, b);
                  QBrush brush(cellColor, k->brush.style());
                  TupColorWidget *cell = k->colors.at(index);
                  cell->setBrush(brush);
                  index++;
             } 
        }
    }
}
