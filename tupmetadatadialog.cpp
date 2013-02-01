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
#ifndef Q_OS_ANDROID
    setWindowTitle(tr("Image Properties"));
    setWindowIcon(QIcon(QPixmap(":images/metadata.png")));
#else
    setStyleSheet("* { background-color: rgb(232,232,232) }");
#endif

    setModal(true);
    QLocale utf(QLocale::AnyLanguage, QLocale::AnyCountry);

    QLabel *titleLabel = new QLabel(tr("Title"));
    if (title.length() == 0)
        k->titleEdit = new QLineEdit(tr("My Picture"));
    else
        k->titleEdit = new QLineEdit(title);
    k->titleEdit->setLocale(utf);

#ifndef Q_OS_ANDROID
    connect(k->titleEdit, SIGNAL(textChanged(const QString &)), this, SLOT(resetTitleColor(const QString &)));
#endif
    titleLabel->setBuddy(k->titleEdit);

    QLabel *topicLabel = new QLabel(tr("Topics"));
    if (topics.length() == 0)
        k->topicEdit = new QLineEdit(tr("#tupitube #2d #fun"));
    else
        k->topicEdit = new QLineEdit(topics);

    k->topicEdit->setLocale(utf);
#ifndef Q_OS_ANDROID
    connect(k->topicEdit, SIGNAL(textChanged(const QString &)), this, SLOT(resetTopicColor(const QString &)));
#endif
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

    QPixmap pixmap(":images/ok.png");
    QIcon buttonIcon(pixmap);
    QPushButton *okButton = new QPushButton(this);
    okButton->setIcon(buttonIcon);
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    okButton->setDefault(true);
    buttonLayout->addWidget(okButton);

    QVBoxLayout *layout = new QVBoxLayout(this);
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

#ifndef Q_OS_ANDROID
void TupMetadataDialog::resetTitleColor(const QString &)
{
    QPalette palette = k->titleEdit->palette();
    if (k->titleEdit->text().length() > 0 && k->titleEdit->text().compare(tr("Set a title for the picture here!")) != 0) 
        palette.setBrush(QPalette::Base, Qt::white);
    else 
        palette.setBrush(QPalette::Base, QColor(255, 140, 138));

    k->titleEdit->setPalette(palette);
}

void TupMetadataDialog::resetTopicColor(const QString &)
{
    QPalette palette = k->topicEdit->palette();
    if (k->topicEdit->text().length() > 0 && k->topicEdit->text().compare(tr("Set some topic tags for the picture here!")) != 0)
        palette.setBrush(QPalette::Base, Qt::white);
    else
        palette.setBrush(QPalette::Base, QColor(255, 140, 138));

    k->topicEdit->setPalette(palette);
}
#endif

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

