#include "tuppathitem.h"
#include "tupsvg2qt.h"
#include "tupserializer.h"

#include <QMimeData>
#include <QBrush>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QPainterPath>
#include <QCursor>

TupPathItem::TupPathItem(QGraphicsItem * parent, QGraphicsScene * scene) : QGraphicsPathItem(parent, scene), m_dragOver(false)
{
    setAcceptDrops(true);
}

TupPathItem::~TupPathItem()
{
}

QDomElement TupPathItem::toXml(QDomDocument &doc) const
{
    QDomElement root = doc.createElement("path");
    
    QString strPath = "";
    QChar t;
    
    for(int i=0; i < path().elementCount(); i++) {
        QPainterPath::Element e = path().elementAt(i);
        switch (e.type) {
            case QPainterPath::MoveToElement:
            {
                if (t != 'M') {
                    t = 'M';
                    strPath += "M " + QString::number(e.x) + " " + QString::number(e.y) + " ";
                } else {
                    strPath += QString::number(e.x) + " " + QString::number(e.y) + " ";
                }
                
            }
            break;
            case QPainterPath::LineToElement:
            {
                if (t != 'L') {
                    t = 'L';
                    strPath += " L " + QString::number(e.x) + " " + QString::number(e.y) + " ";
                } else {
                    strPath += QString::number(e.x) + " " + QString::number(e.y) + " ";
                }
            }
            break;
            case QPainterPath::CurveToElement:
            {
                
                if (t != 'C') {
                    t = 'C';
                    strPath += " C " + QString::number(e.x) + " " + QString::number(e.y) + " ";
                } else {
                    strPath += "  " + QString::number(e.x) + " " + QString::number(e.y) + " ";
                }
            }
            break;
            case QPainterPath::CurveToDataElement:
            {
                if (t == 'C')
                    strPath +=  " " +QString::number(e.x) + "  " + QString::number(e.y) + " ";
            }
            break;
        }
    }
    
    root.setAttribute("coords", strPath);
    
    root.appendChild(TupSerializer::properties(this, doc));
    
    QBrush brush = this->brush();
    root.appendChild(TupSerializer::brush(&brush, doc));
    
    QPen pen = this->pen();
    root.appendChild(TupSerializer::pen(&pen, doc));
    
    return root;
}

void TupPathItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QGraphicsPathItem::paint(painter, option,widget);
}

bool TupPathItem::contains(const QPointF & point) const
{
    return QGraphicsPathItem::contains(point);
}

void TupPathItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasColor()) {
        event->setAccepted(true);
        m_dragOver = true;
        update();
    } else {
        event->setAccepted(false);
    }
}

void TupPathItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    m_dragOver = false;
    update();
}

void TupPathItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    m_dragOver = false;

    if (event->mimeData()->hasColor())
        setBrush(QBrush(qVariantValue<QColor>(event->mimeData()->colorData())));
    else if (event->mimeData()->hasImage())
             setBrush(QBrush(qVariantValue<QPixmap>(event->mimeData()->imageData())));

    update();
}
