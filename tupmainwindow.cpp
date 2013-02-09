/***************************************************************************
 *   Project TUPI: Open 2D Magic                                           *
 *   Component: tupi.mobile                                                *
 *   Project Contact: info@maefloresta.com                                 *
 *   Project Website: http://www.maefloresta.com                           *
 *                                                                         *
 *   Developers:                                                           *
 *   2012:                                                                 *
 *    Gustavo Gonzalez / @xtingray                                         *
 *    Andres Calderon / @andresfcalderon                                   *
 *    Antonio Vanegas / @hpsaturn                                          *
 *                                                                         *
 *   Tupi is a fork of the KTooN project                                   *
 *   KTooN's versions:                                                     *
 *   2006:                                                                 *
 *    David Cuadrado                                                       *
 *    Jorge Cuadrado                                                       *
 *   2003:                                                                 *
 *    Fernado Roldan                                                       *
 *    Simena Dinas                                                         *
 *                                                                         *
 *   Copyright (C) 2012 Mae Floresta - http://www.maefloresta.com          *
 *   License:                                                              *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include "tupmainwindow.h"
#include "tupcanvas.h"
#include "tupstrokesizedialog.h"
#include "tupopacitydialog.h"
#include "tupnethandler.h"
#include "tupabout.h"
#include "tupcolordialog.h"

#ifdef Q_OS_ANDROID
#include "tupmetadataandroiddialog.h"
#include "tupbrushandroiddialog.h"
#include "tupandroidintents.h"
#else
#include "tupmetadatadialog.h"
#include "tupbrushdialog.h"
#endif

#include <QtGui>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QColorDialog>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDebug>
#include <stdlib.h>

struct TupMainWindow::Private
{
   TupCanvas *canvas;
   QGraphicsScene *scene;
   TupNetHandler *net;
   QPen pen;
   double opacity;
   QSize screen;
   QString title;
   QString topics;
   QString description;
};

TupMainWindow::TupMainWindow() : QMainWindow(), k(new Private)
{
#ifndef Q_OS_ANDROID
    setWindowTitle(tr("Tupi: Open 2D Magic"));
    QImage image(":images/tupi.png");
    setWindowIcon(QIcon(QPixmap::fromImage(image)));
#endif

    k->scene = 0;
    k->canvas = 0;
    k->opacity = 1.0;
    k->title = "";
    k->topics = "";
    k->description = "";

    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setCanvas();
    setToolBar();

    k->net = new TupNetHandler();
    connect(k->net, SIGNAL(postReady(const QString &)), this, SLOT(shareURL(const QString &)));
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
#ifndef Q_OS_ANDROID
    QString clearLabel = "Clear Canvas";
#else
    QString clearLabel = "";
#endif
    QImage image0(":images/new.png");
    QAction *clear = new QAction(QIcon(QPixmap::fromImage(image0)), tr("%1").arg(clearLabel), this);
    connect(clear, SIGNAL(triggered()), this, SLOT(newCanvas()));

#ifndef Q_OS_ANDROID
    QString undoLabel = "Undo";
#else
    QString undoLabel = "";
#endif
    QImage image1(":images/undo.png");
    QAction *undo = new QAction(QIcon(QPixmap::fromImage(image1)), undoLabel, this);
    connect(undo, SIGNAL(triggered()), this, SLOT(undo()));
#ifndef Q_OS_ANDROID
    undo->setShortcut(QKeySequence(tr("Ctrl+Z")));
#endif

#ifndef Q_OS_ANDROID
    QString redoLabel = "Redo";
#else
    QString redoLabel = "";
#endif
    QImage image2(":images/redo.png");
    QAction *redo = new QAction(QIcon(QPixmap::fromImage(image2)), redoLabel, this);
    connect(redo, SIGNAL(triggered()), this, SLOT(redo()));
#ifndef Q_OS_ANDROID
    redo->setShortcut(QKeySequence(tr("Ctrl+Y")));
#endif

#ifndef Q_OS_ANDROID
    QString colorLabel = "Palette Color";
#else
    QString colorLabel = "";
#endif
    QImage image3(":images/palette.png");
    QAction *palette = new QAction(QIcon(QPixmap::fromImage(image3)), colorLabel, this);
    connect(palette, SIGNAL(triggered()), this, SLOT(colorDialog()));

#ifndef Q_OS_ANDROID
    QString widthLabel = "Stroke Size";
#else
    QString widthLabel = "";
#endif
    QImage image4(":images/width.png"); 
    QAction *width = new QAction(QIcon(QPixmap::fromImage(image4)), widthLabel, this);
    connect(width, SIGNAL(triggered()), this, SLOT(penStrokeSizeDialog()));

#ifndef Q_OS_ANDROID
    QString opacityLabel = "Stroke Opacity";
#else
    QString opacityLabel = "";
#endif
    QImage image5(":images/opacity.png");
    QAction *opacity = new QAction(QIcon(QPixmap::fromImage(image5)), opacityLabel, this);
    connect(opacity, SIGNAL(triggered()), this, SLOT(opacityDialog()));

#ifndef Q_OS_ANDROID
    QString brushLabel = "Stroke Brush";
#else
    QString brushLabel = "";
#endif
    QImage image6(":images/brush.png");
    QAction *brush = new QAction(QIcon(QPixmap::fromImage(image6)), brushLabel, this);
    connect(brush, SIGNAL(triggered()), this, SLOT(brushDialog()));

#ifndef Q_OS_ANDROID
    QString titleLabel = "Set Title & Description";
#else
    QString titleLabel = "";
#endif
    QImage image7(":images/metadata.png");
    QAction *metadata = new QAction(QIcon(QPixmap::fromImage(image7)), titleLabel, this);
    connect(metadata, SIGNAL(triggered()), this, SLOT(showDialog()));

#ifndef Q_OS_ANDROID
    QString postLabel = "Post Image";
    QImage image8(":images/post.png");
#else
    QString postLabel = "";
    QImage image8(":images/share.png");
#endif
    QAction *post = new QAction(QIcon(QPixmap::fromImage(image8)), postLabel, this);
    connect(post, SIGNAL(triggered()), this, SLOT(postIt()));

#ifndef Q_OS_ANDROID
    QString aboutLabel = "About Tupi";
#else
    QString aboutLabel = "";
#endif
    QImage image9(":images/tupi.png");
    QAction *about = new QAction(QIcon(QPixmap::fromImage(image9)), aboutLabel, this);
    connect(about, SIGNAL(triggered()), this, SLOT(showAbout()));

#ifndef Q_OS_ANDROID
    QImage image10(":images/close.png");
    QAction *exit = new QAction(QIcon(QPixmap::fromImage(image10)), tr("Exit"), this);
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
#endif

    QToolBar *toolbar = new QToolBar(); 
    toolbar->setFloatable(true);

#ifndef Q_OS_ANDROID
    toolbar->setIconSize(QSize(32, 32));
#else
    toolbar->setIconSize(QSize(64, 64));
#endif

    toolbar->addAction(clear);
    toolbar->addAction(undo);
    toolbar->addAction(redo);
    toolbar->addAction(palette);
    toolbar->addAction(width);
    toolbar->addAction(opacity);
    toolbar->addAction(brush);
    toolbar->addAction(metadata);
    toolbar->addAction(post);
    toolbar->addAction(about);

#ifndef Q_OS_ANDROID
    toolbar->addAction(exit);
#endif

    addToolBar(Qt::BottomToolBarArea, toolbar);
}

void TupMainWindow::setMetadata()
{
#ifdef Q_OS_ANDROID
    TupMetadataAndroidDialog *dialog = new TupMetadataAndroidDialog(k->title, k->topics, k->description, this);
    dialog->showMaximized();
#else
    TupMetadataDialog *dialog = new TupMetadataDialog(k->title, k->topics, k->description, this);
    dialog->show();
    QDesktopWidget desktop;
    dialog->move((int) (desktop.screenGeometry().width() - dialog->width())/2,
                 (int) (desktop.screenGeometry().height() - dialog->height())/2);
#endif

    if (dialog->exec() == QDialog::Accepted) {
        k->title = dialog->imageTitle();
        k->topics = dialog->imageTopics();
        k->description = dialog->imageDescription();
    }
}

void TupMainWindow::postIt()
{
    if (k->canvas->isEmpty()) {
        k->canvas->notify("Wow! The canvas is empty. Please, draw something first! ;)");
#ifdef TUP_DEBUG
        qDebug() << "TupMainWindow::postIt() -> Canvas is empty. Please, draw something! ;)";
#endif
    } else {
        int w = k->screen.width();
        int h = k->screen.height();
        TupFrame *frame = k->canvas->frame();

        QDomDocument doc;
        QDomElement root = doc.createElement("mobile");
        root.setAttribute("version", 0);
        doc.appendChild(root);

        if (k->title.length() > 0) {
#ifdef TUP_DEBUG
            qDebug() << "TupMainWindow::postIt() -> Title:" << k->title;
#endif
            QDomElement title = doc.createElement("title");
            QDomText value = doc.createTextNode(k->title);
            title.appendChild(value);
            root.appendChild(title);
        }
        if (k->topics.length() > 0) {
#ifdef TUP_DEBUG
            qDebug() << "TupMainWindow::postIt() -> Topics:" << k->topics;
#endif
            QDomElement topics = doc.createElement("topics");
            QDomText value = doc.createTextNode(k->topics);
            topics.appendChild(value);
            root.appendChild(topics);
        }
        if (k->description.length() > 0) {
#ifdef TUP_DEBUG
            qDebug() << "TupMainWindow::postIt() -> Description:" << k->description;
#endif
            QDomElement description = doc.createElement("description");
            QDomText value = doc.createTextNode(k->description);
            description.appendChild(value);
            root.appendChild(description);
        }

        QDomElement dimension = doc.createElement("dimension");
        QDomText size = doc.createTextNode(QString::number(w) + "," + QString::number(h));
        dimension.appendChild(size);
        root.appendChild(dimension);

        QDomElement package = frame->toXml(doc);
        root.appendChild(package);

        k->net->sendPackage(doc);
    }
}

void TupMainWindow::shareURL(const QString &url)
{
#ifdef Q_OS_ANDROID
    TupAndroidIntents intent;
    intent.setUrl(url);
    // TEST: getMediaStorage
    // qDebug() << "QT MEDIA STORAGE: " << intent.getMediaStorage();
#else
    QDesktopServices::openUrl(url);
#endif
}

void TupMainWindow::showDialog()
{
#ifdef Q_OS_ANDROID
    TupAndroidIntents intent;
    intent.getMediaStorage();
#else
#endif
}
void TupMainWindow::penStrokeSizeDialog()
{
    TupStrokeSizeDialog *dialog = new TupStrokeSizeDialog(k->pen, k->opacity, this);
    connect(dialog, SIGNAL(updatePen(int)), this, SLOT(updatePenStrokeSize(int)));
    dialog->showMaximized();
    dialog->setStrokSize(k->pen.width());
}

void TupMainWindow::colorDialog()
{
    TupColorDialog *dialog = new TupColorDialog(k->pen.brush(), k->screen, this);
    connect(dialog, SIGNAL(updateColor(const QColor)), this, SLOT(updatePenColor(const QColor)));
    dialog->showMaximized();
}

void TupMainWindow::opacityDialog()
{
    TupOpacityDialog *dialog = new TupOpacityDialog(k->pen, k->opacity, this);
    connect(dialog, SIGNAL(updateOpacity(double)), this, SLOT(updatePenOpacity(double)));
    dialog->showMaximized();
    qDebug() << "TupMainWindow::opacityDialog() - opacity: " << k->opacity;
    dialog->setOpacityValue(k->opacity);
}

void TupMainWindow::brushDialog()
{
#ifdef Q_OS_ANDROID
    TupBrushAndroidDialog *dialog = new TupBrushAndroidDialog(k->pen, k->screen, this);
#else
    TupBrushDialog *dialog = new TupBrushDialog(k->pen, this);
#endif
    connect(dialog, SIGNAL(updatePenBrush(Qt::BrushStyle)), this, SLOT(updatePenBrush(Qt::BrushStyle)));
    dialog->showMaximized();
}

void TupMainWindow::updatePenStrokeSize(int size)
{
    k->pen.setWidth(size);
    k->canvas->updatePenStrokeSize(size);
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
    if (!k->canvas->isEmpty())
        k->canvas->clear();
}

void TupMainWindow::showAbout()
{
    TupAbout *dialog = new TupAbout(this);
    dialog->showMaximized();
}
