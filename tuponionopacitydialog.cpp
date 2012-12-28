#include "tuponionopacitydialog.h"
#include "tuppenthicknesswidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <cmath>

struct TupOnionOpacityDialog::Private
{
    QVBoxLayout *innerLayout;
    TupPenThicknessWidget *opacityPreview;
    QLabel *sizeLabel;
    QColor color;
    double currentOpacity;
};

TupOnionOpacityDialog::TupOnionOpacityDialog(const QColor &color, double opacity, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);

    k->color = color;
    k->currentOpacity = opacity;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(2);

    k->innerLayout = new QVBoxLayout;

    setOpacityCanvas();
    setButtonsPanel();

    QPixmap pixmap(":images/close_big.png");
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

TupOnionOpacityDialog::~TupOnionOpacityDialog()
{
}

void TupOnionOpacityDialog::setOpacityCanvas()
{
    k->opacityPreview = new TupPenThicknessWidget(this);
    k->opacityPreview->setColor(k->color);
    k->opacityPreview->setBrush(Qt::SolidPattern);
    k->opacityPreview->render(k->currentOpacity);
    
    k->innerLayout->addWidget(k->opacityPreview);
}

void TupOnionOpacityDialog::setButtonsPanel()
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

    QString number = QString::number(k->currentOpacity);
    if (number.length() == 3)
        number = number + "0";

    k->sizeLabel = new QLabel(number);
    k->sizeLabel->setFont(QFont("Arial", 24, QFont::Bold));
    k->sizeLabel->setAlignment(Qt::AlignHCenter);
    k->sizeLabel->setFixedWidth(65);

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
    layout->addWidget(k->sizeLabel);
    layout->addWidget(plus);
    layout->addWidget(plus5);

    k->innerLayout->addLayout(layout);
}

void TupOnionOpacityDialog::fivePointsLess()
{
    modifySize(-0.05);
}

void TupOnionOpacityDialog::onePointLess()
{
    modifySize(-0.01);
}

void TupOnionOpacityDialog::onePointMore()
{
    modifySize(0.01);
}

void TupOnionOpacityDialog::fivePointsMore()
{
    modifySize(0.05);
}

void TupOnionOpacityDialog::modifySize(double value)
{
    k->currentOpacity = (100 * k->currentOpacity)/100;
    k->currentOpacity += value;

    if (k->currentOpacity > 1)
        k->currentOpacity = 1;

    if (k->currentOpacity < 0)
        k->currentOpacity = 0;

    if (k->currentOpacity == 0) {
        k->sizeLabel->setText("0.00");
    } else if (k->currentOpacity == 1) {
        k->sizeLabel->setText("1.00");
    } else {
        QString number = QString::number(k->currentOpacity);
        if (number.length() == 3)
            number = number + "0";
        k->sizeLabel->setText(number);
    }

    k->opacityPreview->render(k->currentOpacity);

    emit updateOpacity(k->currentOpacity);
}
