#include "tupmainwindow.h"
#include "tupcanvas.h"
#include "tupnethandler.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QInputDialog>

struct TupMainWindow::Private
{
   TupCanvas *canvas;
   QGraphicsScene *scene;
   TupNetHandler *net;
   QSize screen;
};

TupMainWindow::TupMainWindow() : QMainWindow(), k(new Private)
{
    setWindowTitle(tr("Tupi"));
    setMouseTracking(true);
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
    QAction *post = new QAction(QIcon("images/post.png"), tr("&Post"), this);
    post->setStatusTip(tr("Post in Tupitube"));
    connect(post, SIGNAL(triggered()), this, SLOT(postIt()));

    QToolBar *toolbar = new QToolBar(); 
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

    qDebug() << "TupMainWindow::setCanvas() - w: " << k->screen.width();
    qDebug() << "TupMainWindow::setCanvas() - h: " << k->screen.height();

    k->canvas = new TupCanvas(k->scene, this);
    k->canvas->setRenderHints(QPainter::Antialiasing);

    setCentralWidget(k->canvas);
}

void TupMainWindow::postIt()
{
    // QRect rect = k->canvas->rect();
    int w = k->screen.width();
    int h = k->screen.height();
    qDebug() << "TupMainWindow::postIt() - w: " << w;
    qDebug() << "TupMainWindow::postIt() - h: " << h;

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
