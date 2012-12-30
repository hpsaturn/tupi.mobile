#include "tuppalettedialog.h"
#include "tupcolorwidget.h"

#include <QBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QDialogButtonBox>

struct TupPaletteDialog::Private
{
    QVBoxLayout *innerLayout;
    QList<TupColorWidget *> colors;
    int currentColorIndex;
    QBrush brush;
    QColor color;
    QSize size;
};

TupPaletteDialog::TupPaletteDialog(const QBrush brush, const QSize size, QWidget *parent) : QDialog(parent), k(new Private)
{
    setModal(true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("* { background-color: rgb(232,232,232) }");

    k->brush = brush;
    k->size = size;
    k->currentColorIndex = -1;

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(10);

    k->innerLayout = new QVBoxLayout;

    setColorsArray();

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

TupPaletteDialog::~TupPaletteDialog()
{
}

void TupPaletteDialog::setColorsArray()
{
    int w = k->size.width();
    int h = k->size.height();
    int rows = w / 100;
    int columns = h / 50;

    int index = 0;
    for (int j=0; j<rows; j++) {
         QBoxLayout *matrix = new QHBoxLayout;
         matrix->setSpacing(10);

         for (int i=0; i<columns; i++) {
              int r = qrand() % (255 + 1);
              int g = qrand() % (255 + 1);
              int b = qrand() % (255 + 1);

              QColor color(r, g, b);
              QBrush brush(color, k->brush.style());
              TupColorWidget *button = new TupColorWidget(index, brush);
              connect(button, SIGNAL(clicked(int)), this, SLOT(updateMatrix(int)));
              index++;
              k->colors << button;
              matrix->addWidget(button);
         }

         k->innerLayout->addLayout(matrix);
    }
}

void TupPaletteDialog::updateMatrix(int index)
{
    if (index != k->currentColorIndex) {
        if (k->currentColorIndex >= 0) {
            TupColorWidget *button = (TupColorWidget *) k->colors.at(k->currentColorIndex);
            button->unselect();
        }
        TupColorWidget *selection = (TupColorWidget *) k->colors.at(index);
        k->color = selection->color();
        k->currentColorIndex = index;
    }
}

void TupPaletteDialog::closeDialog()
{
    emit updateColor(k->color);
    close();
}
