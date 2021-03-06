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

#include "tuprgbeditor.h"
#include "tupcolorwidget.h"
#include "tupslider.h"

#include <QBoxLayout>
#include <QLabel>
#include <QDebug>

struct TupRGBEditor::Private
{
    QBoxLayout *layout;
    QColor color;
    Qt::BrushStyle style;
    TupColorWidget *panel;
    QLabel *redLabel;
    QLabel *greenLabel;
    QLabel *blueLabel;
    TupSlider *red;
    TupSlider *green;
    TupSlider *blue;
    int r;
    int g;
    int b;
};

TupRGBEditor::TupRGBEditor(const QBrush brush, QWidget *parent) : QWidget(parent), k(new Private)
{
    k->r = brush.color().red();
    k->g = brush.color().green();
    k->b = brush.color().blue();
    k->style = brush.style();

    k->panel = new TupColorWidget(1, brush, QSize(150, 150), false);
    k->panel->setEditable(false);

    QVBoxLayout *colorPanel = new QVBoxLayout;
    colorPanel->setAlignment(Qt::AlignHCenter);
    colorPanel->addWidget(k->panel);

    k->redLabel = new QLabel("Red: " + QString::number(k->r));
    k->redLabel->setFont(QFont("Arial", 16, QFont::Normal));
    k->redLabel->setAlignment(Qt::AlignHCenter);

    k->red = new TupSlider(Qt::Horizontal, TupSlider::Color, QColor(0, 0, 0), QColor(255, 0, 0));
    k->red->setRange(0, 255);
    k->red->setValue(k->r);
    connect(k->red, SIGNAL(valueChanged(int)), this, SLOT(updateRedCompound(int)));

    QHBoxLayout *redPanel = new QHBoxLayout;
    redPanel->setContentsMargins(40, 0, 40, 0);
    redPanel->setAlignment(Qt::AlignHCenter);
    redPanel->addWidget(k->red);

    k->greenLabel = new QLabel("Green: " + QString::number(k->r));
    k->greenLabel->setFont(QFont("Arial", 16, QFont::Normal));
    k->greenLabel->setAlignment(Qt::AlignHCenter);

    k->green = new TupSlider(Qt::Horizontal, TupSlider::Color, QColor(0, 0, 0), QColor(0, 255, 0));
    k->green->setRange(0, 255);
    k->green->setValue(k->g);
    connect(k->green, SIGNAL(valueChanged(int)), this, SLOT(updateGreenCompound(int)));

    QHBoxLayout *greenPanel = new QHBoxLayout;
    greenPanel->setContentsMargins(40, 0, 40, 0);
    greenPanel->setAlignment(Qt::AlignHCenter);
    greenPanel->addWidget(k->green);

    k->blueLabel = new QLabel("Blue: " + QString::number(k->r));
    k->blueLabel->setFont(QFont("Arial", 16, QFont::Normal));
    k->blueLabel->setAlignment(Qt::AlignHCenter);

    k->blue = new TupSlider(Qt::Horizontal, TupSlider::Color, QColor(0, 0, 0), QColor(0, 0, 255));
    k->blue->setRange(0, 255);
    k->blue->setValue(k->b);
    connect(k->blue, SIGNAL(valueChanged(int)), this, SLOT(updateBlueCompound(int)));

    QHBoxLayout *bluePanel = new QHBoxLayout;
    bluePanel->setContentsMargins(40, 0, 40, 0);
    bluePanel->setAlignment(Qt::AlignHCenter);
    bluePanel->addWidget(k->blue);

    k->layout = new QVBoxLayout(this);
    k->layout->setContentsMargins(3, 3, 3, 3);
    k->layout->setSpacing(5);
    k->layout->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    k->layout->addLayout(colorPanel);
    k->layout->addSpacing(5);
    k->layout->addWidget(k->redLabel);
    k->layout->addLayout(redPanel);
    k->layout->addWidget(k->greenLabel);
    k->layout->addLayout(greenPanel);
    k->layout->addWidget(k->blueLabel);
    k->layout->addLayout(bluePanel);
}

TupRGBEditor::~TupRGBEditor()
{
}

void TupRGBEditor::updateRedCompound(int red)
{
    k->r = red;
    QColor color(k->r, k->g, k->b); 
    k->panel->setBrush(QBrush(color, k->style));
    k->redLabel->setText("Red: " + QString::number(k->r));
    emit updateColor(color);
}

void TupRGBEditor::updateGreenCompound(int green)
{
    k->g = green;
    QColor color(k->r, k->g, k->b);
    k->panel->setBrush(QBrush(color, k->style));
    k->greenLabel->setText("Green: " + QString::number(k->g));
    emit updateColor(color);
}

void TupRGBEditor::updateBlueCompound(int blue)
{
    k->b = blue;
    QColor color(k->r, k->g, k->b);
    k->panel->setBrush(QBrush(color, k->style));
    k->blueLabel->setText("Blue: " + QString::number(k->b));
    emit updateColor(color);
}

void TupRGBEditor::setCurrentColor(const QColor color)
{
    k->r = color.red();
    k->g = color.green();
    k->b = color.blue();

    k->panel->setBrush(QBrush(color, k->style));
    k->redLabel->setText("Red: " + QString::number(k->r));
    k->greenLabel->setText("Green: " + QString::number(k->g));
    k->blueLabel->setText("Blue: " + QString::number(k->b));
    k->red->setValue(k->r);
    k->green->setValue(k->g);
    k->blue->setValue(k->b);
}
