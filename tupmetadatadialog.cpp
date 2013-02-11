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

#include "tupmetadatadialog.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLocale>

struct TupMetadataDialog::Private
{
    QLineEdit *titleEdit;
    QLineEdit *topicEdit;
    QTextEdit *descText;
};

TupMetadataDialog::TupMetadataDialog(const QString &title, const QString &topics, const QString &description, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::Popup);

    QLabel *label = new QLabel(tr("Image Properties"));
    label->setFont(QFont("Arial", 16, QFont::Normal));
    label->setAlignment(Qt::AlignHCenter);

    QLocale utf(QLocale::AnyLanguage, QLocale::AnyCountry);
    QLabel *titleLabel = new QLabel(tr("Title"));
    if (title.length() == 0)
        k->titleEdit = new QLineEdit(tr("My Picture"));
    else
        k->titleEdit = new QLineEdit(title);
    k->titleEdit->setLocale(utf);
    titleLabel->setBuddy(k->titleEdit);

    QLabel *topicLabel = new QLabel(tr("Topics"));
    if (topics.length() == 0)
        k->topicEdit = new QLineEdit(tr("#tupitube #2d #mobile"));
    else
        k->topicEdit = new QLineEdit(topics);

    k->topicEdit->setLocale(utf);
    topicLabel->setBuddy(k->topicEdit);

    QLabel *descLabel = new QLabel(tr("Description"));

    k->descText = new QTextEdit;
    k->descText->setLocale(utf);
    k->descText->setAcceptRichText(false);
    k->descText->setFixedHeight(80);

    if (description.length() == 0)
        k->descText->setText(tr("Just a little taste of my style :)"));
    else
        k->descText->setText(description);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(titleLabel);
    topLayout->addWidget(k->titleEdit);

    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(topicLabel);
    middleLayout->addWidget(k->topicEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);

    QPixmap newPixmap(":images/new.png");
    QIcon newIcon(newPixmap);
    QPushButton *newButton = new QPushButton(this);
    newButton->setToolTip(tr("Clear"));
    newButton->setIcon(newIcon);
    connect(newButton, SIGNAL(clicked()), this, SLOT(clean()));
    newButton->setDefault(true);
    buttonLayout->addWidget(newButton);

    QPixmap okPixmap(":images/ok.png");
    QIcon okIcon(okPixmap);
    QPushButton *okButton = new QPushButton(this);
    okButton->setToolTip(tr("Ok"));
    okButton->setIcon(okIcon);
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    okButton->setDefault(true);
    buttonLayout->addWidget(okButton);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(5);

    layout->addWidget(label);
    layout->addLayout(topLayout);
    layout->addLayout(middleLayout);
    layout->addWidget(descLabel);
    layout->addWidget(k->descText);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

TupMetadataDialog::~TupMetadataDialog()
{
}

QString TupMetadataDialog::imageTitle() const
{
    return QString::fromUtf8(k->titleEdit->text().toUtf8());
}

QString TupMetadataDialog::imageTopics() const
{
    return QString::fromUtf8(k->topicEdit->text().toUtf8());
}

QString TupMetadataDialog::imageDescription() const
{
    return QString::fromUtf8(k->descText->toPlainText().toUtf8());
}

void TupMetadataDialog::clean()
{
    k->titleEdit->clear();
    k->topicEdit->clear();
    k->descText->clear();
}

