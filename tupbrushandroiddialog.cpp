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

#include "tupbrushandroiddialog.h"
#include "tupcolorwidget.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QDebug>

struct TupBrushAndroidDialog::Private
{
    QVBoxLayout *innerLayout;
    QGridLayout *brushesLayout;
    QList<TupColorWidget *> brushes;
    int currentBrushIndex;
    Qt::BrushStyle brushStyle;
    QPen pen;
    QSize size;
};

TupBrushAndroidDialog::TupBrushAndroidDialog(const QPen pen, const QSize size, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("* { background-color: rgb(232,232,232) }");
 
    k->pen = pen;
    k->size = size;
    k->currentBrushIndex = -1;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(10);

    k->innerLayout = new QVBoxLayout;

    setLabelPanel();
    k->brushesLayout = new QGridLayout;
    k->innerLayout->addLayout(k->brushesLayout);

    {
        for(int index=1;index<=7*2;index++)
        {
            QBrush brush(k->pen.color(), Qt::BrushStyle(index));
            TupColorWidget* button = new TupColorWidget(index, brush, QSize(10, 10));


            k->brushes.push_back(button);
            connect(button, SIGNAL(clicked(int)), this, SLOT(updateSelection(int)));
        }
    }

    setBrushOptions();

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

TupBrushAndroidDialog::~TupBrushAndroidDialog()
{
}

void TupBrushAndroidDialog::setLabelPanel()
{
    QLabel *label = new QLabel("Brushes");
    label->setFont(QFont("Arial", 24, QFont::Bold));
    label->setAlignment(Qt::AlignHCenter);
    label->setFixedHeight(50);
    k->innerLayout->addWidget(label);
}

void TupBrushAndroidDialog::setBrushOptions()
{

    QList<TupColorWidget*>::iterator i;

    for (i = k->brushes.begin(); i != k->brushes.end(); ++i)
        k->brushesLayout->removeWidget(*i);

    int w,h;

    if (this->size().width() > this->size().height())
        w = k->size.width(), h = k->size.height();
    else
        w = k->size.height(), h = k->size.width();


    int rows = 0;
    int columns = 0;

    if (w < h) {
        rows = 2;
        columns = 7;
    } else {
        rows = 7;
        columns = 2;
    }

    int cellW = (w - 100)/columns;
    int cellH = (h - 100)/rows;

    if (w < h) {
        if (cellH > cellW)
            cellH = cellW;
    } else {
        if (cellW > cellH)
            cellW = cellH;
    }

#ifdef TUP_DEBUG
    qDebug() << "TupBrushAndroidDialog::setBrushOptions() - width: " << w;
    qDebug() << "TupBrushAndroidDialog::setBrushOptions() - height: " << h;
    qDebug() << "TupBrushAndroidDialog::setBrushOptions() - cellW: " << cellW;
    qDebug() << "TupBrushAndroidDialog::setBrushOptions() - cellH: " << cellH;
    qDebug() << "TupBrushAndroidDialog::setBrushOptions() - rows: " << rows;
    qDebug() << "TupBrushAndroidDialog::setBrushOptions() - columns: " << columns;

#endif

    int index = 0;
    for (int i=0; i<rows; i++) {


         for (int j=0; j<columns; j++) {
              //QBrush brush(k->pen.color(), Qt::BrushStyle(index));
              //TupColorWidget* button = new TupColorWidget(index, brush, QSize(cellW, cellH));
              //k->buttons.push_back(button);
              //connect(button, SIGNAL(clicked(int)), this, SLOT(updateSelection(int)));
              //k->brushes << button;
             k->brushes.at(index)->setFixedSize(QSize(cellW,cellH));
             k->brushesLayout->addWidget(k->brushes.at(index),i,j);
             index++;

         }

    }
}

void TupBrushAndroidDialog::updateSelection(int index)
{
    if (index != k->currentBrushIndex) {
        if (k->currentBrushIndex > 0) {
            TupColorWidget *button = (TupColorWidget *) k->brushes.at(k->currentBrushIndex - 1);
            button->unselected();
        }
        k->currentBrushIndex = index;
    }
}

void TupBrushAndroidDialog::closeDialog()
{
    if (k->currentBrushIndex > 0) 
        emit updatePenBrush(Qt::BrushStyle(k->currentBrushIndex));

    close();
}

void TupBrushAndroidDialog::paintEvent ( QPaintEvent * event )
{
    setBrushOptions();
}
