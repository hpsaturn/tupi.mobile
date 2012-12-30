#include "tupmainwindow.h"
#include "tupcanvas.h"
#include "tuppalettedialog.h"
#include "tuppenwidthdialog.h"
#include "tupopacitydialog.h"
#include "tupbrushdialog.h"
#include "tupnethandler.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QInputDialog>

struct TupMainWindow::Private
{
   TupCanvas *canvas;
   QGraphicsScene *scene;
   TupNetHandler *net;
   QPen pen;
   double opacity;
   QSize screen;
};

TupMainWindow::TupMainWindow() : QMainWindow(), k(new Private)
{
    k->scene = 0;
    k->canvas = 0;
    k->opacity = 1.0;

    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setCanvas();
    setToolBar();

    k->net = new TupNetHandler();
    connect(k->net, SIGNAL(postReady(const QString &)), this, SLOT(showURLDialog(const QString &)));
}

TupMainWindow::~TupMainWindow()
{
}

void TupMainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}

void TupMainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    setCanvas();
}

void TupMainWindow::setCanvas()
{
    k->pen = QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    k->screen = QSize(width() - 100, height() - 100);
    QRectF rect = QRectF(QPointF(0, 0), k->screen);
    k->scene = new QGraphicsScene;
    k->scene->setSceneRect(rect);

    k->canvas = new TupCanvas(k->scene, k->pen, k->opacity, this);
    k->canvas->setRenderHints(QPainter::Antialiasing);

    setCentralWidget(k->canvas);
}

void TupMainWindow::setToolBar()
{
    QImage image0(":images/undo.png");
    QAction *undo = new QAction(QIcon(QPixmap::fromImage(image0)), "", this);
    connect(undo, SIGNAL(triggered()), this, SLOT(undo()));

    QImage image1(":images/redo.png");
    QAction *redo = new QAction(QIcon(QPixmap::fromImage(image1)), "", this);
    connect(redo, SIGNAL(triggered()), this, SLOT(redo()));

    QImage image2(":images/palette.png");
    QAction *palette = new QAction(QIcon(QPixmap::fromImage(image2)), "", this);
    connect(palette, SIGNAL(triggered()), this, SLOT(colorDialog()));

    QImage image3(":images/width.png"); 
    QAction *width = new QAction(QIcon(QPixmap::fromImage(image3)), "", this);
    connect(width, SIGNAL(triggered()), this, SLOT(penWidthDialog()));

    QImage image4(":images/opacity.png");
    QAction *opacity = new QAction(QIcon(QPixmap::fromImage(image4)), "", this);
    connect(opacity, SIGNAL(triggered()), this, SLOT(opacityDialog()));

    QImage image5(":images/brush.png");
    QAction *brush = new QAction(QIcon(QPixmap::fromImage(image5)), "", this);
    connect(brush, SIGNAL(triggered()), this, SLOT(brushDialog()));

    QImage image6(":images/post.png");
    QAction *post = new QAction(QIcon(QPixmap::fromImage(image6)), "", this);
    connect(post, SIGNAL(triggered()), this, SLOT(postIt()));

    QImage image7(":images/new.png");
    QAction *clear = new QAction(QIcon(QPixmap::fromImage(image7)), "", this);
    connect(clear, SIGNAL(triggered()), this, SLOT(newCanvas()));

    QImage image8(":images/close.png");
    QAction *exit = new QAction(QIcon(QPixmap::fromImage(image8)), "", this);
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

    QToolBar *toolbar = new QToolBar(); 
    toolbar->setIconSize(QSize(48, 48));
    toolbar->addAction(undo);
    toolbar->addAction(redo);
    toolbar->addAction(palette);
    toolbar->addAction(width);
    toolbar->addAction(opacity);
    toolbar->addAction(brush);
    toolbar->addAction(post);
    toolbar->addAction(clear);
    toolbar->addAction(exit);

    addToolBar(Qt::BottomToolBarArea, toolbar);
}

void TupMainWindow::postIt()
{
    int w = k->screen.width();
    int h = k->screen.height();
    TupFrame *frame = k->canvas->frame();

    QDomDocument doc;
    QDomElement root = doc.createElement("mobile");
    doc.appendChild(root);

    QDomElement dimension = doc.createElement("dimension");
    QDomText size = doc.createTextNode(QString::number(w) + "," + QString::number(h));
    dimension.appendChild(size);
    root.appendChild(dimension);

    QDomElement package = frame->toXml(doc);
    root.appendChild(package);

    k->net->sendPackage(doc);
}

void TupMainWindow::showURLDialog(const QString &message)
{
    bool ok;
    QString text = QInputDialog::getText(this, "Let's share!",
                                         "Post it?", QLineEdit::Normal,
                                         message, &ok);
    if (ok && !text.isEmpty())
        qDebug() << "Posting message in social networks..."; 
}

void TupMainWindow::penWidthDialog()
{
    TupPenWidthDialog *dialog = new TupPenWidthDialog(k->pen, k->opacity, this);
    connect(dialog, SIGNAL(updatePen(int)), this, SLOT(updatePenWidth(int)));
    dialog->showMaximized();
}

void TupMainWindow::colorDialog()
{
    TupPaletteDialog *dialog = new TupPaletteDialog(k->pen.brush(), k->screen, this);
    connect(dialog, SIGNAL(updateColor(const QColor)), this, SLOT(updatePenColor(const QColor)));
    dialog->showMaximized();
}

void TupMainWindow::opacityDialog()
{
    TupOpacityDialog *dialog = new TupOpacityDialog(k->pen, k->opacity, this);
    connect(dialog, SIGNAL(updateOpacity(double)), this, SLOT(updatePenOpacity(double)));
    dialog->showMaximized();
}

void TupMainWindow::brushDialog()
{
    TupBrushDialog *dialog = new TupBrushDialog(k->pen, k->opacity, this);
    connect(dialog, SIGNAL(updatePenBrush(Qt::BrushStyle)), this, SLOT(updatePenBrush(Qt::BrushStyle)));
    dialog->showMaximized();
}

void TupMainWindow::updatePenWidth(int width)
{
    k->pen.setWidth(width);
    k->canvas->updatePenSize(width);
}

void TupMainWindow::updatePenColor(const QColor color)
{
    QBrush brush(color, k->pen.brush().style());
    k->pen.setBrush(brush); 
    k->canvas->updatePenColor(color);
}

void TupMainWindow::updatePenOpacity(double opacity)
{
    k->opacity = opacity;
    k->canvas->updatePenOpacity(opacity);
}

void TupMainWindow::updatePenBrush(Qt::BrushStyle brushStyle)
{
    QBrush brush = k->pen.brush();
    brush.setStyle(brushStyle);
    k->pen.setBrush(brush);
    k->canvas->updatePenBrush(brushStyle);
}

void TupMainWindow::undo()
{
    k->canvas->undo();
}

void TupMainWindow::redo()
{
    k->canvas->redo();
}

void TupMainWindow::newCanvas()
{
    k->canvas->clear();
}
