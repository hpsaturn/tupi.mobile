#ifndef __TUPGRAPHICALGORITHM_H__
#define __TUPGRAPHICALGORITHM_H__

#include <QString>
#include <QPolygon>
#include <QPainterPath>

/**
 * @author Jorge Cuadrado
 */

class TupGraphicalAlgorithm
{
    private:
        TupGraphicalAlgorithm() {}
        ~TupGraphicalAlgorithm() {};
        
    public:
        static QPainterPath bezierFit(QPolygonF &points_, float error, int from = 0, int to = -1);
        static QPolygonF polygonFit(const QPolygonF &points);
        static bool intersectLine(const QPointF &start, const QPointF& end, const QRectF& rect);
        static char calculateCode(const QPointF &point, const QRectF &window);
        static double distanceToPoint(const QPointF &pos);
        static double angleForPos(const QPointF &pos, const QPointF &anchor = QPointF(0,0));
        
    private:
        enum CohenSutherlandCode
        {
            Bit1 = 1<<1,
            Bit2 = 1<<2,
            Bit3 = 1<<3,
            Bit4 = 1<<4
        };
        
        static void printCode(char code);
};

#endif
