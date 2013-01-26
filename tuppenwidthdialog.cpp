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

#include "tuppenwidthdialog.h"
#include "tuppenpreviewcanvas.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>

struct TupPenWidthDialog::Private
{
    QVBoxLayout *innerLayout;
    TupPenPreviewCanvas *thickPreview;
    QPen pen;
    double opacity;
    QLabel *sizeLabel;
    int currentSize;
};

TupPenWidthDialog::TupPenWidthDialog(QPen pen, double opacity, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("* { background-color: rgb(232,232,232) }");

    k->pen = pen;
    k->opacity = opacity;
    k->currentSize = k->pen.width();

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(2);

    k->innerLayout = new QVBoxLayout;

    setBrushCanvas();
    setLabelPanel();
    setButtonsPanel();

    QPixmap pixmap(":images/close.png");
    QIcon buttonIcon(pixmap);
    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(buttonIcon);
    closeButton->setIconSize(pixmap.rect().size());
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton(closeButton, QDialogButtonBox::ActionRole);

    k->innerLayout->addSpacing(10);
    k->innerLayout->addWidget(buttonBox);

    layout->addLayout(k->innerLayout);
}

TupPenWidthDialog::~TupPenWidthDialog()
{
}

void TupPenWidthDialog::setBrushCanvas()
{
    k->thickPreview = new TupPenPreviewCanvas(k->pen, k->opacity, this);
    k->innerLayout->addWidget(k->thickPreview);
}

void TupPenWidthDialog::setLabelPanel()
{
    k->sizeLabel = new QLabel("Width: " + QString::number(k->currentSize));
    k->sizeLabel->setFont(QFont("Arial", 24, QFont::Bold));
    k->sizeLabel->setAlignment(Qt::AlignHCenter);

    k->innerLayout->addWidget(k->sizeLabel);
}

void TupPenWidthDialog::setButtonsPanel()
{
    QPixmap pixmap(":images/minus_sign_big.png");
    QIcon buttonIcon(pixmap);
    QPushButton *minus5 = new QPushButton(this);
    minus5->setToolTip(tr("-5"));
    minus5->setIcon(buttonIcon);
    minus5->setIconSize(pixmap.rect().size());

    connect(minus5, SIGNAL(clicked()), this, SLOT(fivePointsLess()));

    QPixmap pixmap2(":images/minus_sign_small.png");
    QIcon buttonIcon2(pixmap2);
    QPushButton *minus = new QPushButton(this);
    minus->setToolTip(tr("-1"));
    minus->setIcon(buttonIcon2);
    minus->setIconSize(pixmap2.rect().size());
    connect(minus, SIGNAL(clicked()), this, SLOT(onePointLess()));

    QPixmap pixmap3(":images/plus_sign_small.png");
    QIcon buttonIcon3(pixmap3);
    QPushButton *plus = new QPushButton(this);
    plus->setToolTip(tr("+1"));
    plus->setIcon(buttonIcon3);
    plus->setIconSize(pixmap3.rect().size());
    connect(plus, SIGNAL(clicked()), this, SLOT(onePointMore()));

    QPixmap pixmap4(":images/plus_sign_big.png");
    QIcon buttonIcon4(pixmap4);
    QPushButton *plus5 = new QPushButton(this);
    plus5->setToolTip(tr("+5"));
    plus5->setIcon(buttonIcon4);
    plus5->setIconSize(pixmap4.rect().size());

    connect(plus5, SIGNAL(clicked()), this, SLOT(fivePointsMore()));

    QBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(minus5);
    layout->addWidget(minus);
    layout->addWidget(plus);
    layout->addWidget(plus5);

    k->innerLayout->addLayout(layout);
}

void TupPenWidthDialog::fivePointsLess()
{
    modifySize(-5);
}

void TupPenWidthDialog::onePointLess()
{
    modifySize(-1);
}

void TupPenWidthDialog::onePointMore()
{
    modifySize(1);
}

void TupPenWidthDialog::fivePointsMore()
{
    modifySize(5);
}

void TupPenWidthDialog::modifySize(int value)
{
    k->currentSize += value;
    if (k->currentSize > 100)
        k->currentSize = 100;

    if (k->currentSize < 1)
        k->currentSize = 1;

    k->thickPreview->render(k->currentSize);
    k->sizeLabel->setText("Width: " + QString::number(k->currentSize));

    emit updatePen(k->currentSize);
}

