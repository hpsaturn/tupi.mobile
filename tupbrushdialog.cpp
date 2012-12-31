#include "tupbrushdialog.h"
#include "tupcolorwidget.h"

#include <QBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QDialogButtonBox>

struct TupBrushDialog::Private
{
    QVBoxLayout *innerLayout;
    QList<TupColorWidget *> brushes;
    int currentBrushIndex;
    Qt::BrushStyle brushStyle;
    QPen pen;
    QSize size;
};

TupBrushDialog::TupBrushDialog(const QPen pen, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("* { background-color: rgb(232,232,232) }");
 
    k->pen = pen;
    k->currentBrushIndex = -1;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(10);

    k->innerLayout = new QVBoxLayout;

    setBrushOptions();

    QPixmap pixmap(":images/close.png");
    QIcon buttonIcon(pixmap);
    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(buttonIcon);
    closeButton->setIconSize(pixmap.rect().size());
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton(closeButton, QDialogButtonBox::ActionRole);

    k->innerLayout->addSpacing(10);
    k->innerLayout->addWidget(buttonBox);

    layout->addLayout(k->innerLayout);
}

TupBrushDialog::~TupBrushDialog()
{
}

void TupBrushDialog::setBrushOptions()
{
    int index = 1;
    for (int j=0; j<2; j++) {
         QBoxLayout *matrix = new QHBoxLayout;
         matrix->setSpacing(10);

         for (int i=0; i<7; i++) {
              QBrush brush(k->pen.color(), Qt::BrushStyle(index));
              TupColorWidget *button = new TupColorWidget(index, brush);
              connect(button, SIGNAL(clicked(int)), this, SLOT(updateSelection(int)));
              index++;
              k->brushes << button;
              matrix->addWidget(button);
         }

         k->innerLayout->addLayout(matrix);
    }
}

void TupBrushDialog::updateSelection(int index)
{
    if (index != k->currentBrushIndex) {
        if (k->currentBrushIndex > 0) {
            TupColorWidget *button = (TupColorWidget *) k->brushes.at(k->currentBrushIndex - 1);
            button->unselect();
        }
        k->currentBrushIndex = index;
    }
}

void TupBrushDialog::closeDialog()
{
    if (k->currentBrushIndex > 0) 
        emit updatePenBrush(Qt::BrushStyle(k->currentBrushIndex));

    close();
}
