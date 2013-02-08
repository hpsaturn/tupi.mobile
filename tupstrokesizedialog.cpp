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

#include "tupstrokesizedialog.h"
#include "tuppenpreviewcanvas.h"
#include "tupcolorslider.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDebug>

struct TupStrokeSizeDialog::Private
{
    QVBoxLayout *innerLayout;
    TupPenPreviewCanvas *thickPreview;
    QPen pen;
    TupColorSlider *slider;
    double opacity;
    QLabel *sizeLabel;
    int currentSize;
};

TupStrokeSizeDialog::TupStrokeSizeDialog(QPen pen, double opacity, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::Popup);
    setStyleSheet("* { background-color: rgb(232,232,232) }");

    k->pen = pen;
    k->opacity = opacity;
    k->currentSize = k->pen.width();

    QBoxLayout *layout = new QHBoxLayout(this);
#ifdef Q_OS_ANDROID
    layout->setContentsMargins(3, 3, 3, 3);
#else
    layout->setContentsMargins(5, 5, 5, 5);
#endif
    layout->setSpacing(2);

    k->innerLayout = new QVBoxLayout;

    setLabelPanel();
    setBrushCanvas();
    setSlider();

    QPixmap pixmap(":images/close.png");
    QIcon buttonIcon(pixmap);
    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(buttonIcon);
    closeButton->setToolTip(tr("Close"));
#ifdef Q_OS_ANDROID
    closeButton->setIconSize(pixmap.rect().size());
#endif
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton(closeButton, QDialogButtonBox::ActionRole);

    k->innerLayout->addSpacing(5);
    k->innerLayout->addWidget(buttonBox);

    layout->addLayout(k->innerLayout);
}

TupStrokeSizeDialog::~TupStrokeSizeDialog()
{
}

void TupStrokeSizeDialog::setBrushCanvas()
{
    k->thickPreview = new TupPenPreviewCanvas(k->pen, k->opacity, this);
    k->innerLayout->addWidget(k->thickPreview);
}

void TupStrokeSizeDialog::setLabelPanel()
{
    k->sizeLabel = new QLabel("Size: " + QString::number(k->currentSize));
#ifdef Q_OS_ANDROID
    k->sizeLabel->setFont(QFont("Arial", 24, QFont::Bold));
#else
    k->sizeLabel->setFont(QFont("Arial", 16, QFont::Normal));
#endif
    k->sizeLabel->setAlignment(Qt::AlignHCenter);
    k->innerLayout->addWidget(k->sizeLabel);
}

void TupStrokeSizeDialog::setSlider()
{
    k->slider = new TupColorSlider(Qt::Horizontal, TupColorSlider::Size, k->pen.color(), k->pen.color());
    k->slider->setBrushSettings(k->pen.brush().style(), k->opacity);
    k->slider->setRange(1, 100);
    connect(k->slider, SIGNAL(valueChanged(int)), this, SLOT(modifySize(int)));

    QWidget *widget = new QWidget;
    widget->setFixedHeight(100);
    QBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(k->slider);
    
    k->innerLayout->addWidget(widget);
}

void TupStrokeSizeDialog::modifySize(int value)
{
    k->currentSize = value;

#ifdef TUP_DEBUG
    qDebug() << "TupStrokeSizeDialog::modifySize() - Size: " << k->currentSize;
#endif

    k->thickPreview->render(k->currentSize);
    k->sizeLabel->setText("Size: " + QString::number(k->currentSize));

    emit updatePen(k->currentSize);
}

void TupStrokeSizeDialog::setStrokSize(int value)
{
    k->slider->setValue(value);
    modifySize(value);
}
