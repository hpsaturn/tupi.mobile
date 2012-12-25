#ifndef TUPPATHITEM_H
#define TUPPATHITEM_H

#include <QGraphicsPathItem>
#include <QDomElement>

/**
 * @author David Cuadrado
*/

class TupPathItem : public QGraphicsPathItem
{
    public:
        TupPathItem(QGraphicsItem * parent = 0, QGraphicsScene * scene = 0);
        ~TupPathItem();
        
        QDomElement toXml(QDomDocument &doc) const;
        virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
        bool contains(const QPointF & point) const;
        
    protected:
        virtual void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
        virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
        virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
        
    private:
        bool m_dragOver;
};

#endif
