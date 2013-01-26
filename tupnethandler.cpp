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

#include "tupnethandler.h"
#include <QMessageBox>

struct TupNetHandler::Private
{
    QTcpSocket *socket;
};

TupNetHandler::TupNetHandler() : QObject(), k(new Private)
{
}

TupNetHandler::~TupNetHandler()
{
}

void TupNetHandler::sendPackage(const QDomDocument &doc)
{
    QString data = doc.toString();

    qDebug() << "Tracing TupNetHandler::sendPackage()";
    qDebug() << data;

    k->socket = new QTcpSocket;
    k->socket->connectToHost("tupitube.com", 8080, QIODevice::ReadWrite);
    connect(k->socket, SIGNAL(readyRead ()), this, SLOT(readFromServer()));
    connect(k->socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
   
    bool connected = k->socket->waitForConnected(1000);

    if (connected) {
        if (k->socket->state() == QAbstractSocket::ConnectedState) {
            QTextStream stream(k->socket);
            stream << data.toLocal8Bit().toBase64() << "%%" << endl;
        }
    } else {
        errorDialog();
    }
}

void TupNetHandler::readFromServer()
{
    QString readed;

    while (k->socket->canReadLine()) {
           readed += k->socket->readLine();
           if (readed.endsWith("%%\n"))
               break;
    }

    if (!readed.isEmpty()) {
        readed.remove(readed.lastIndexOf("%%"), 2);
        readed = QString::fromLocal8Bit(QByteArray::fromBase64(readed.toLocal8Bit()));
    }

    if (k->socket->canReadLine())
        readFromServer();

    emit postReady(readed);

    k->socket->disconnectFromHost();
}

void TupNetHandler::displayError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    errorDialog();
}

void TupNetHandler::errorDialog()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Fatal Error"),
                       tr("Tupitube service is down! :( \nPlease, try it later."), 0);
    msgBox.addButton(tr("Ok"), QMessageBox::AcceptRole);
    msgBox.exec();
}
