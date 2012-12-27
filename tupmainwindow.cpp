#include "tupmainwindow.h"
#include "tupcanvas.h"
#include "tuppendialog.h"
#include "tupnethandler.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QDesktopWidget>

struct TupMainWindow::Private
{
   TupCanvas *canvas;
   QGraphicsScene *scene;
   TupNetHandler *net;
   TupBrushManager *brushManager;
   QSize screen;
};

TupMainWindow::TupMainWindow() : QMainWindow(), k(new Private)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    k->brushManager = new TupBrushManager(this);
    QPen pen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    k->brushManager->setPen(pen);

    setToolBar();
    setCanvas();

    k->net = new TupNetHandler();
    connect(k->net, SIGNAL(postReady(const QString &)), this, SLOT(showDialog(const QString &)));
}

TupMainWindow::~TupMainWindow()
{
}

void TupMainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}

void TupMainWindow::setToolBar()
{
    QImage image(":images/pen_properties.png"); 
    QAction *brush = new QAction(QIcon(QPixmap::fromImage(image)), tr("&Pen Size"), this);
    brush->setStatusTip(tr("Pen Size"));
    connect(brush, SIGNAL(triggered()), this, SLOT(penDialog()));

    QImage image2(":images/post.png");
    QAction *post = new QAction(QIcon(QPixmap::fromImage(image2)), tr("&Post"), this);
    post->setStatusTip(tr("Post in Tupitube"));
    connect(post, SIGNAL(triggered()), this, SLOT(postIt()));

    QToolBar *toolbar = new QToolBar(); 
    toolbar->addAction(brush);
    toolbar->addAction(post);

    addToolBar(Qt::BottomToolBarArea, toolbar);
}

void TupMainWindow::setCanvas()
{
    // k->screen = QSize(width(), height());
    k->screen = QSize(520, 380);
    QRectF rect = QRectF(QPointF(0, 0), k->screen);
    k->scene = new QGraphicsScene;
    k->scene->setSceneRect(rect);

    k->canvas = new TupCanvas(k->scene, k->brushManager->pen(), this);
    k->canvas->setRenderHints(QPainter::Antialiasing);

    setCentralWidget(k->canvas);
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

void TupMainWindow::showDialog(const QString &message)
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
    QDesktopWidget desktop;
    TupPenDialog *dialog = new TupPenDialog(k->brushManager, this);
    connect(dialog, SIGNAL(updatePen(int)), this, SLOT(updatePenSize(int)));

    QApplication::restoreOverrideCursor();

    dialog->show();
    dialog->move((int) (desktop.screenGeometry().width() - dialog->width())/2 ,
                        (int) (desktop.screenGeometry().height() - dialog->height())/2);
}

void TupMainWindow::updatePenSize(int size)
{
    k->brushManager->setPenSize(size);    
    k->canvas->updatePenSize(size);
}
