#include "tuppendialog.h"
#include "tuppenthicknesswidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>

struct TupPenDialog::Private
{
    QVBoxLayout *innerLayout;
    TupPenThicknessWidget *thickPreview;
    QPen pen;
    QLabel *sizeLabel;
    int currentSize;
};

TupPenDialog::TupPenDialog(const QPen pen, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);

    k->pen = pen;
    k->currentSize = k->pen.width();

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(2);

    k->innerLayout = new QVBoxLayout;

    setBrushCanvas();
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

TupPenDialog::~TupPenDialog()
{
}

void TupPenDialog::setBrushCanvas()
{
    k->thickPreview = new TupPenThicknessWidget(this);
    k->thickPreview->setColor(k->pen.color());
    k->thickPreview->setBrush(k->pen.brush().style());
    k->thickPreview->render(k->currentSize);
    
    k->innerLayout->addWidget(k->thickPreview);
}

void TupPenDialog::setButtonsPanel()
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

    k->sizeLabel = new QLabel(QString::number(k->currentSize));
    k->sizeLabel->setFont(QFont("Arial", 24, QFont::Bold));
    k->sizeLabel->setAlignment(Qt::AlignHCenter);
    k->sizeLabel->setFixedWidth(40);

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

void TupPenDialog::fivePointsLess()
{
    modifySize(-5);
}

void TupPenDialog::onePointLess()
{
    modifySize(-1);
}

void TupPenDialog::onePointMore()
{
    modifySize(1);
}

void TupPenDialog::fivePointsMore()
{
    modifySize(5);
}

void TupPenDialog::modifySize(int value)
{
    k->currentSize += value;
    if (k->currentSize > 100)
        k->currentSize = 100;

    if (k->currentSize < 1)
        k->currentSize = 1;

    k->thickPreview->render(k->currentSize);
    k->sizeLabel->setText(QString::number(k->currentSize));

    emit updatePen(k->currentSize);
}

