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

    // k->innerLayout->addWidget(k->sizeLabel, Qt::AlignHCenter);
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

