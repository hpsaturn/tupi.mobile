#include "tupframe.h"
#include "tuppathitem.h"

#include <QHash>
#include <QTextStream>
#include <QDebug>

struct TupFrame::Private
{
    QHash<int, TupPathItem *> graphics;
};

TupFrame::TupFrame() : QObject(), k(new Private)
{
}

TupFrame::~TupFrame()
{
}

QDomElement TupFrame::toXml(QDomDocument &doc) const
{
    QDomElement root = doc.createElement("frame");
    doc.appendChild(root);

    QHashIterator<int, TupPathItem *> i(k->graphics);
    while (i.hasNext()) {
           i.next();
           QDomElement object = doc.createElement("object");
           TupPathItem *item = (TupPathItem *) i.value();
           object.appendChild(item->toXml(doc));
           root.appendChild(object);
    }

    return root;
}

void TupFrame::addItem(TupPathItem *item)
{
    int index = k->graphics.size();
    k->graphics.insert(index, item);

    QDomDocument doc;
    QDomElement xml = item->toXml(doc);
    QString newDoc;
    QTextStream text(&newDoc);
    text << xml;

    qDebug() << "Object!";
    qDebug() << newDoc;
}

void TupFrame::removeItem(int index)
{
    k->graphics.remove(index);
}
