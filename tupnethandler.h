#ifndef TUPNETHANDLER_H
#define TUPNETHANDLER_H

#include <QTcpSocket>
#include <QDomDocument>

class TupNetHandler : public QObject
{
    Q_OBJECT

    public:
        TupNetHandler();
        ~TupNetHandler();
        void sendPackage(const QDomDocument &doc);

    signals:
        void postReady(const QString &);

    private slots:
        void readFromServer();

    private:
        struct Private;
        Private *const k;
};

#endif
