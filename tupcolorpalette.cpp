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

#include "tupcolorpalette.h"
#include "tupcolorwidget.h"
#include "tupseparator.h"
#include "tupcolorslider.h"

#include <cmath>
#include <QTabWidget>
#include <QFrame>
#include <QBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QDebug>

struct TupColorPalette::Private
{
    QBoxLayout *paletteGlobalLayout;
    QBoxLayout *colorMatrixLayout;
    QBoxLayout *centralLayout;
    QList<TupColorWidget *> colors;
    QList<TupColorWidget *> baseColors;
    int currentColorIndex;
    int currentBaseColor;
    int currentLeadColor;
    QBrush brush;
    QColor color;
    int rows;
    int columns;
    TupColorSlider *slider;
    TupColorWidget *top;
    TupColorWidget *bottom;
};

TupColorPalette::TupColorPalette(const QBrush brush, const QSize size, QWidget *parent) : QWidget(parent), k(new Private)
{
    k->brush = brush;
    k->currentLeadColor = 255;
    k->currentColorIndex = -1;
    int w = size.width();
    int h = size.height();
    k->columns = w/70;
    k->rows = h/50;

    QBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(10);
    k->colorMatrixLayout = new QVBoxLayout;

    k->paletteGlobalLayout = new QVBoxLayout;
    k->centralLayout = new QHBoxLayout;

    initColorsArray();
    setSliderPanel();

    k->centralLayout->addWidget(new TupSeparator(Qt::Vertical));
    k->centralLayout->addLayout(k->colorMatrixLayout);
    k->paletteGlobalLayout->addLayout(k->centralLayout);

    setBaseColorsPanel();
    layout->addLayout(k->paletteGlobalLayout);
}

TupColorPalette::~TupColorPalette()
{
}

void TupColorPalette::setSliderPanel()
{
    QBoxLayout *sliderLayout = new QVBoxLayout;
    sliderLayout->setAlignment(Qt::AlignVCenter);

    QColor topColor(255, 0, 0);
    QBrush topBrush(topColor, k->brush.style());
    k->top = new TupColorWidget(1, topBrush, QSize(30, 20));
    k->top->setEditable(false);
    sliderLayout->addWidget(k->top);

    k->slider = new TupColorSlider(QColor(255,0,0),QColor(0,0,0));
    k->slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    k->slider->setRange(0, 255);
   // k->slider->setValue(255);

    sliderLayout->addWidget(k->slider);
    connect(k->slider, SIGNAL(valueChanged(int)), this, SLOT(updateMatrixFromSlider(int)));

    QColor bottomColor(0, 0, 0);
    QBrush bottomBrush(bottomColor, k->brush.style());
    k->bottom = new TupColorWidget(1, bottomBrush, QSize(30, 20));
    k->bottom->setEditable(false);
    sliderLayout->addWidget(k->bottom);

    k->centralLayout->addLayout(sliderLayout);
}

void TupColorPalette::setBaseColorsPanel()
{
    k->currentBaseColor = 0;
    QColor redColor(255, 0, 0);
    QBrush redBrush(redColor, k->brush.style());
    TupColorWidget *red = new TupColorWidget(0, redBrush, QSize(50, 30));
    red->selected();
    connect(red, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << red;

    QColor greenColor(0, 255, 0);
    QBrush greenBrush(greenColor, k->brush.style());
    TupColorWidget *green = new TupColorWidget(1, greenBrush, QSize(50, 30));
    connect(green, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << green;

    QColor blueColor(0, 0, 255);
    QBrush blueBrush(blueColor, k->brush.style());
    TupColorWidget *blue = new TupColorWidget(2, blueBrush, QSize(50, 30));
    connect(blue, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << blue;

    QColor whiteColor(255, 255, 255);
    QBrush whiteBrush(whiteColor, k->brush.style());
    TupColorWidget *white = new TupColorWidget(3, whiteBrush, QSize(50, 30));
    connect(white, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
    k->baseColors << white;

    QBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setAlignment(Qt::AlignHCenter);
    bottomLayout->setContentsMargins(3, 3, 3, 3);
    bottomLayout->setSpacing(10);
    bottomLayout->addWidget(red);
    bottomLayout->addWidget(green);
    bottomLayout->addWidget(blue);
    bottomLayout->addWidget(white);

    k->paletteGlobalLayout->addWidget(new TupSeparator(Qt::Horizontal));
    k->paletteGlobalLayout->addLayout(bottomLayout);
}

void TupColorPalette::initColorsArray()
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
              TupColorWidget *button = new TupColorWidget(index, brush, QSize(50, 30));
              connect(button, SIGNAL(clicked(int)), this, SLOT(updateSelection(int)));
              index++;
              k->colors << button;
              matrix->addWidget(button);
         }
         k->colorMatrixLayout->addLayout(matrix);
    }
}

void TupColorPalette::updateSelection(int index)
{
    if (index != k->currentColorIndex) {
        if (k->currentColorIndex >= 0) {
            TupColorWidget *button = (TupColorWidget *) k->colors.at(k->currentColorIndex);
            button->unselected();
        }
        TupColorWidget *selection = (TupColorWidget *) k->colors.at(index);
        k->color = selection->color();
        k->currentColorIndex = index;
        emit updateColor(k->color);
    }
}

void TupColorPalette::updateMatrixFromSlider(int value)
{
    k->currentLeadColor = value;
    updateMatrix(k->currentBaseColor, true);
}

void TupColorPalette::updateMatrix(int newColor, bool fromSlider)
{
    if (k->currentColorIndex >= 0 && !fromSlider) {
        TupColorWidget *button = (TupColorWidget *) k->colors.at(k->currentColorIndex);
        button->unselected();
    }

    TupColorWidget *current = (TupColorWidget *) k->baseColors.at(newColor);

    k->slider->setColors(current->color(),QColor(0,0,0));

    if (!fromSlider) {
        k->color = current->color();
        if (k->color == Qt::white) {
            k->top->setBrush(QBrush(Qt::black));
            k->bottom->setBrush(QBrush(Qt::white));
            k->slider->setEnabled(false);
        } else {
            k->top->setBrush(QBrush(k->color));
            if (!k->slider->isEnabled()) {
                k->slider->setEnabled(true);
                k->bottom->setBrush(QBrush(Qt::black));
            }
        }
    }

    if ((newColor != k->currentBaseColor) && !fromSlider)
        k->baseColors.at(k->currentBaseColor)->unselected(); 

    k->currentBaseColor = newColor;
    int deltaX = 255 / k->rows;
    int deltaY = 255 / k->columns;
    int delta = ceil(255.0 / (k->rows * k->columns));

    int r = 0;
    int g = 0;
    int b = 0;
    int index = 0;
    TupColorPalette::Color color = TupColorPalette::Color(newColor);

    for (int i=0; i < k->rows; i++) {
         for (int j=0; j < k->columns; j++) {
              switch (color) {
                      case TupColorPalette::Red :
                           r = k->currentLeadColor;
                           g = (i*deltaY);
                           b = (j*deltaX);
                      break;
                      case TupColorPalette::Green :
                           r = (i*deltaX);
                           g = k->currentLeadColor;
                           b = (j*deltaX);
                      break;
                      case TupColorPalette::Blue :
                           r = (i*deltaX);
                           g = (j*deltaY);
                           b = k->currentLeadColor;
                      break;
                      case TupColorPalette::White :
                           if (j == k->columns - 1 && i == k->rows - 1) {
                               r = 255;
                               g = 255;
                               b = 255;
                           } else {
                               r += delta;
                               g += delta;
                               b += delta;
                           }
                      break;
              }

#ifdef TUP_DEBUG
              // qDebug() << "TupColorPalette::updateMatrix() - [r,g,b]: " << r << ", " << g << ", " << b;
#endif
              if (r > 255)
                  r = 255;
              if (g > 255)
                  g = 255;
              if (b > 255)
                  b = 255;

              QColor cellColor(r, g, b);
              QBrush brush(cellColor, k->brush.style());
              TupColorWidget *cell = k->colors.at(index);
              cell->setBrush(brush);
              index++;
        } 

        if (k->currentColorIndex >= 0 && fromSlider) {
            TupColorWidget *last = (TupColorWidget *) k->colors.at(k->currentColorIndex);
            k->color = last->color();
        }

        emit updateColor(k->color);
    }
}
