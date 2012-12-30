#include "tupopacitydialog.h"
#include "tuppenpreviewcanvas.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <cmath>

struct TupOpacityDialog::Private
{
    QVBoxLayout *innerLayout;
    TupPenPreviewCanvas *opacityPreview;
    QLabel *sizeLabel;
    QPen pen;
    double currentOpacity;
};

TupOpacityDialog::TupOpacityDialog(QPen pen, double opacity, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("* { background-color: rgb(232,232,232) }");

    k->pen = pen;
    k->currentOpacity = opacity;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(2);

    k->innerLayout = new QVBoxLayout;

    setOpacityCanvas();
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

TupOpacityDialog::~TupOpacityDialog()
{
}

void TupOpacityDialog::setOpacityCanvas()
{
    k->opacityPreview = new TupPenPreviewCanvas(k->pen, k->currentOpacity, this);
    k->innerLayout->addWidget(k->opacityPreview);
}

void TupOpacityDialog::setLabelPanel()
{
    QString number = QString::number(k->currentOpacity);
    if (number.length() == 3)
        number = number + "0";

    k->sizeLabel = new QLabel("Opacity: " + number);
    k->sizeLabel->setFont(QFont("Arial", 24, QFont::Bold));
    k->sizeLabel->setAlignment(Qt::AlignHCenter);

    k->innerLayout->addWidget(k->sizeLabel);
}

void TupOpacityDialog::setButtonsPanel()
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

void TupOpacityDialog::fivePointsLess()
{
    modifySize(-0.05);
}

void TupOpacityDialog::onePointLess()
{
    modifySize(-0.01);
}

void TupOpacityDialog::onePointMore()
{
    modifySize(0.01);
}

void TupOpacityDialog::fivePointsMore()
{
    modifySize(0.05);
}

void TupOpacityDialog::modifySize(double value)
{
    k->currentOpacity = (100 * k->currentOpacity)/100;
    k->currentOpacity += value;

    if (k->currentOpacity > 1)
        k->currentOpacity = 1;

    if (k->currentOpacity < 0)
        k->currentOpacity = 0;

    if (k->currentOpacity == 0) {
        k->sizeLabel->setText("Opacity: 0.00");
    } else if (k->currentOpacity == 1) {
        k->sizeLabel->setText("Opacity: 1.00");
    } else {
        QString number = QString::number(k->currentOpacity);
        if (number.length() == 3)
            number = number + "0";
        k->sizeLabel->setText("Opacity: " + number);
    }

    k->opacityPreview->render(k->currentOpacity);

    emit updateOpacity(k->currentOpacity);
}
