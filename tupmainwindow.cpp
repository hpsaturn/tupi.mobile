#include "tupmainwindow.h"
#include "tupcanvas.h"
#include "tuppendialog.h"
#include "tuponionopacitydialog.h"
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

    k->screen = this->size();
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
    QAction *brush = new QAction(QIcon(QPixmap::fromImage(image3)), "", this);
    connect(brush, SIGNAL(triggered()), this, SLOT(penDialog()));

    QImage image4(":images/opacity.png");
    QAction *opacity = new QAction(QIcon(QPixmap::fromImage(image4)), "", this);
    connect(opacity, SIGNAL(triggered()), this, SLOT(opacityDialog()));

    QImage image5(":images/post.png");
    QAction *post = new QAction(QIcon(QPixmap::fromImage(image5)), "", this);
    connect(post, SIGNAL(triggered()), this, SLOT(postIt()));

    QImage image6(":images/new.png");
    QAction *clear = new QAction(QIcon(QPixmap::fromImage(image6)), "", this);
    connect(clear, SIGNAL(triggered()), this, SLOT(newCanvas()));

    QToolBar *toolbar = new QToolBar(); 
    toolbar->addAction(undo);
    toolbar->addAction(redo);
    toolbar->addAction(palette);
    toolbar->addAction(brush);
    toolbar->addAction(opacity);
    toolbar->addAction(post);
    toolbar->addAction(clear);

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

void TupMainWindow::penDialog()
{
    TupPenDialog *dialog = new TupPenDialog(k->pen, this);
    connect(dialog, SIGNAL(updatePen(int)), this, SLOT(updatePenSize(int)));
    dialog->showMaximized();
}

void TupMainWindow::colorDialog()
{
    QColor color = QColorDialog::getColor(k->pen.color(), this);
    k->canvas->updateColor(color);
}

void TupMainWindow::opacityDialog()
{
    TupOnionOpacityDialog *dialog = new TupOnionOpacityDialog(k->pen.color(), k->opacity, this);
    connect(dialog, SIGNAL(updateOpacity(double)), this, SLOT(setOnionOpacity(double)));
    dialog->showMaximized();
}

void TupMainWindow::updatePenSize(int width)
{
    k->pen.setWidth(width);
    k->canvas->updatePenSize(width);
}

void TupMainWindow::setOnionOpacity(double opacity)
{
    k->opacity = opacity;
    k->canvas->updatePenOpacity(opacity);
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




