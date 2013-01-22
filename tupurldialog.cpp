#include "tupurldialog.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>

TupUrlDialog::TupUrlDialog(const QString &url, QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setWindowTitle("Let's share!");

    QLabel *link = new QLabel();
    link->setAlignment(Qt::AlignCenter);
    link->setText("<a href=\"" + url + "\">" + url + "</a>");
    link->setTextFormat(Qt::RichText);
    link->setTextInteractionFlags(Qt::TextBrowserInteraction);
    link->setOpenExternalLinks(true);

    QPushButton *postButton = new QPushButton(tr("Post it!"));
    postButton->setDefault(true);

    QPushButton *cancelButton = new QPushButton(tr("Cancel"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(postButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(link);
    layout->addWidget(buttonBox);

    setLayout(layout);
}
