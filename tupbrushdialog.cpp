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

#include "tupbrushdialog.h"
#include "tupcolorwidget.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QDialogButtonBox>

struct TupBrushDialog::Private
{
    QVBoxLayout *innerLayout;
    QList<TupColorWidget *> brushes;
    int currentBrushIndex;
    Qt::BrushStyle brushStyle;
    QPen pen;
    QSize size;
};

TupBrushDialog::TupBrushDialog(const QPen pen, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    k->pen = pen;
    k->currentBrushIndex = -1;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(10);

    k->innerLayout = new QVBoxLayout;

    setLabelPanel();
    setBrushOptions();
    layout->addLayout(k->innerLayout);
}

TupBrushDialog::~TupBrushDialog()
{
}

void TupBrushDialog::setLabelPanel()
{
    QLabel *label = new QLabel("Brushes");
    label->setFont(QFont("Arial", 16, QFont::Normal));
    label->setAlignment(Qt::AlignHCenter);
    k->innerLayout->addWidget(label);
}

void TupBrushDialog::setBrushOptions()
{
    int index = 1;
    for (int j=0; j<4; j++) {
         QBoxLayout *matrix = new QHBoxLayout;
         matrix->setSpacing(10);

         for (int i=0; i<4; i++) {
              if (index < 15) {
                  QBrush brush(k->pen.color(), Qt::BrushStyle(index));
                  TupColorWidget *button = new TupColorWidget(index, brush, QSize(50, 50), false);
                  connect(button, SIGNAL(clicked(int)), this, SLOT(updateSelection(int)));
                  index++;
                  k->brushes << button;
                  matrix->addWidget(button);
              } else {
                  if (j == 3 && i == 3) {
                      QPixmap pixmap(":images/close.png");
                      QIcon buttonIcon(pixmap);
                      QPushButton *closeButton = new QPushButton(this);
                      closeButton->setIcon(buttonIcon);
                      closeButton->setToolTip(tr("Close"));
                      closeButton->setDefault(true);
                      connect(closeButton, SIGNAL(clicked()), this, SLOT(closeDialog()));
                      matrix->addWidget(closeButton);
                  } else {
                      matrix->addWidget(new QWidget());
                  }
              }
         }

         k->innerLayout->addLayout(matrix);
    }
}

void TupBrushDialog::updateSelection(int index)
{
    if (index != k->currentBrushIndex) {
        if (k->currentBrushIndex > 0) {
            TupColorWidget *button = (TupColorWidget *) k->brushes.at(k->currentBrushIndex - 1);
            button->unselected();
        }
        k->currentBrushIndex = index;
    }
}

void TupBrushDialog::closeDialog()
{
    if (k->currentBrushIndex > 0) 
        emit updatePenBrush(Qt::BrushStyle(k->currentBrushIndex));

    close();
}
