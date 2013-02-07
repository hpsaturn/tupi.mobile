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

#include "tupcolordialog.h"

#ifndef Q_OS_ANDROID
#include "tupcolorpalette.h"
#include "tuprgbeditor.h"
#else
#include "tupcolorandroidpalette.h"
#endif

#include <QTabWidget>
#include <QBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QDebug>

struct TupColorDialog::Private
{
    QBoxLayout *layout;
    QColor color;
};

TupColorDialog::TupColorDialog(const QBrush brush, const QSize size, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::Popup);
    setStyleSheet("* { background-color: rgb(232,232,232); }");

    k->color = brush.color();

    k->layout = new QVBoxLayout(this);
    k->layout->setContentsMargins(3, 3, 3, 3);
    k->layout->setSpacing(10);

#ifdef Q_OS_ANDROID
    TupColorPaletteAndroid *palette = new TupColorPaletteAndroid(brush, size, this);
#else
    TupColorPalette *palette = new TupColorPalette(brush, size, this);
#endif
    connect(palette, SIGNAL(updateColor(const QColor)), this, SLOT(setCurrentColor(const QColor)));

    QTabWidget *tabs = new QTabWidget;
    tabs->setFont(QFont("Arial", 14, QFont::Normal));
    tabs->addTab(palette, tr("Basic Palette"));

#ifndef Q_OS_ANDROID
    TupRGBEditor *editor = new TupRGBEditor(brush, this);
    connect(editor, SIGNAL(updateColor(const QColor)), this, SLOT(setCurrentColor(const QColor)));
    connect(palette, SIGNAL(updateColor(const QColor)), editor, SLOT(setCurrentColor(const QColor)));
    tabs->addTab(editor, tr("RGB Editor"));
#endif

    k->layout->addWidget(tabs);

    setClosePanel();
}

TupColorDialog::~TupColorDialog()
{
}

void TupColorDialog::setClosePanel()
{
    QPixmap pixmap(":images/close.png");
    QIcon buttonIcon(pixmap);
    QPushButton *closeButton = new QPushButton;
    closeButton->setIcon(buttonIcon);
    closeButton->setToolTip(tr("Close"));
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton(closeButton, QDialogButtonBox::ActionRole);
    buttonBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    k->layout->addWidget(buttonBox);
}

void TupColorDialog::closeDialog()
{
    emit updateColor(k->color);
    close();
}

void TupColorDialog::setCurrentColor(const QColor color)
{
    k->color = color;
}
