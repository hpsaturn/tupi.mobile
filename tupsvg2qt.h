#ifndef TUPSVG2QT_H
#define TUPSVG2QT_H

#include <QString>
#include <QPainterPath>
#include <QPen>
#include <QXmlAttributes>
#include <QBrush>

class TupSvg2Qt
{
    private:
        TupSvg2Qt();
        ~TupSvg2Qt();
        
    public:
        static bool svgpath2qtpath(const QString &data, QPainterPath &path);
        static bool svgmatrix2qtmatrix(const QString &data, QMatrix &matrix);
        static bool parsePointF(const QString &pointstr, QPointF &point);
        
        static void parsePen(QPen &pen, const QXmlAttributes &attributes);
        static bool parseBrush(QBrush &brush, const QXmlAttributes &attributes);
        
        static QList<qreal> parseNumbersList(QString::const_iterator &itr);
};

#endif
