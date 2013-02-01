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
#include "tuppalettedialog.h"
#include "tuppenwidthdialog.h"
#include "tupopacitydialog.h"
#include "tupbrushdialog.h"
#include "tupnethandler.h"
#include "tupdialog.h"

#ifdef Q_OS_ANDROID
#include "android_intents.h"
#endif

#include <QtGui>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QDesktopServices>
#include <stdlib.h>
#include <QDebug>

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
#ifndef Q_OS_ANDROID
    setWindowTitle(tr("Tupi: Open 2D Magic"));
    QImage image(":images/tupi.png");
    setWindowIcon(QIcon(QPixmap::fromImage(image)));
#endif

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
    QString redoLabel = "Redo";
#else
    QString redoLabel = "";
#endif
    QImage image2(":images/redo.png");
    QAction *redo = new QAction(QIcon(QPixmap::fromImage(image2)), redoLabel, this);
    connect(redo, SIGNAL(triggered()), this, SLOT(redo()));

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
    connect(width, SIGNAL(triggered()), this, SLOT(penWidthDialog()));

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
    QString postLabel = "Post Image";
#else
    QString postLabel = "";
#endif
    QImage image7(":images/post.png");
    QAction *post = new QAction(QIcon(QPixmap::fromImage(image7)), postLabel, this);
    connect(post, SIGNAL(triggered()), this, SLOT(postIt()));

#ifndef Q_OS_ANDROID
    QImage image8(":images/close.png");
    QAction *exit = new QAction(QIcon(QPixmap::fromImage(image8)), tr("Exit"), this);
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
#endif

    QToolBar *toolbar = new QToolBar(); 
    toolbar->setIconSize(QSize(60, 60));
    toolbar->addAction(clear);
    toolbar->addAction(undo);
    toolbar->addAction(redo);
    toolbar->addAction(palette);
    toolbar->addAction(width);
    toolbar->addAction(opacity);
    toolbar->addAction(brush);
    toolbar->addAction(post);

#ifndef Q_OS_ANDROID
    toolbar->addAction(exit);
#endif

    addToolBar(Qt::BottomToolBarArea, toolbar);
}

void TupMainWindow::postIt()
{
    if (k->canvas->isEmpty()) {
        TupDialog::self()->display(tr("Wow!"), tr("Canvas is empty. Please, draw something! ;)"), TupDialog::Error);
#ifdef TUP_DEBUG
        qDebug() << "TupMainWindow::postIt() -> Canvas is empty. Please, draw something! ;)";
#endif
    } else {
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
}

void TupMainWindow::showURLDialog(const QString &url)
{
#ifdef Q_OS_ANDROID
    AndroidIntents intent;
    intent.setUrl(url);
#else
    QDesktopServices::openUrl(url);
#endif
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
    TupBrushDialog *dialog = new TupBrushDialog(k->pen, this);
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
