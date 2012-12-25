#ifndef TUPFRAME_H
#define TUPFRAME_H

#include "tuppathitem.h"

class TupFrame : public QObject
{
    Q_OBJECT

    public:
       TupFrame();
       ~TupFrame();
       void addItem(TupPathItem *item);
       void removeItem(int index);
       
    public:
       QDomElement toXml(QDomDocument &doc) const;
       
    private:
       struct Private;
       Private *const k;
};

#endif
