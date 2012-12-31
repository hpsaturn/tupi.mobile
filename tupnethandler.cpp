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

