#ifndef TUPSERIALIZER_H
#define TUPSERIALIZER_H

#include <QDomDocument>
#include <QDomElement>
#include <QXmlAttributes>
#include <QBrush>
#include <QPen>

class QGraphicsItem;

class TupSerializer
{
    public:
        TupSerializer();
        ~TupSerializer();
        
        static QDomElement properties(const QGraphicsItem *item, QDomDocument &doc);
        static void loadProperties(QGraphicsItem *item, const QXmlAttributes &atts);
        static void loadProperties(QGraphicsItem *item, const QDomElement &e);
        
        static QDomElement gradient(const QGradient *gradient, QDomDocument &doc);
        static QGradient * createGradient(const QXmlAttributes &atts);
        
        static QDomElement brush(const QBrush *brush, QDomDocument &doc);
        static void loadBrush(QBrush &brush, const QXmlAttributes &atts);
        static void loadBrush(QBrush &brush, const QDomElement &e);
        
        static QDomElement pen(const QPen *pen, QDomDocument &doc);
        static void loadPen(QPen &pen, const QXmlAttributes &atts);
        static void loadPen(QPen &pen, const QDomElement &e);
        
        static QDomElement font(const QFont *font, QDomDocument &doc);
        static void loadFont(QFont &font, const QDomElement &e);
        static void loadFont(QFont &font, const QXmlAttributes &atts);
};        

#endif
