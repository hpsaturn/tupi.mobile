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

#include "tupabout.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QIcon>
#include <QPushButton>
#include <QFile>

struct TupAbout::Private
{
};

TupAbout::TupAbout(QWidget *parent) : QDialog(parent), k(new Private)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setModal(true);
    setStyleSheet("* { background-color: rgb(232,232,232) }");

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(5);

    QVBoxLayout *innerLayout = new QVBoxLayout;
    innerLayout->setContentsMargins(5, 5, 5, 5);
    innerLayout->setSpacing(10);

    QImage image(":images/about.png");
    QLabel *icon = new QLabel("");
    icon->setAlignment(Qt::AlignHCenter);
    icon->setPixmap(QPixmap::fromImage(image)); 

    QLabel *title = new QLabel("tupi.mobile 1.0");
    title->setFont(QFont("Arial", 12, QFont::Bold));
    title->setAlignment(Qt::AlignHCenter);

    QFile file(":resources/about.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString line = ""; 
    while (!file.atEnd()) {
           line += file.readLine();
    }

    QTextEdit *description = new QTextEdit;
    description->setStyleSheet("* { background-color: rgb(255,255,255) }");
    description->setText(line);
    description->setReadOnly(true);

    QPixmap pixmap(":images/close.png");
    QIcon buttonIcon(pixmap);
    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(buttonIcon);
    closeButton->setIconSize(pixmap.rect().size());
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    innerLayout->addWidget(icon);  
    innerLayout->addWidget(title);    
    innerLayout->addWidget(description);
    innerLayout->addWidget(closeButton);

    layout->addLayout(innerLayout);
    setFixedSize(QSize(400, 360));
}

TupAbout::~TupAbout()
{
}
