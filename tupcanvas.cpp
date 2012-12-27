#include "tupcanvas.h"
#include "tuppathitem.h"

#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsEllipseItem>

struct TupCanvas::Private
{
   QGraphicsScene *scene;
   TupFrame *frame;
   TupPathItem *item;

   QPainterPath path;
   QPointF firstPoint;
   QPointF oldPos;
   QPen pen;
   int size;

   bool pressed;
};

TupCanvas::TupCanvas(QGraphicsScene *scene, const QPen pen, QWidget *parent) : QGraphicsView(scene, parent), k(new Private)
{
    centerOn(k->scene->sceneRect().center());
    setInteractive(true);
    setMouseTracking(true);
    setScene(scene);

    k->scene = scene;
    k->pen = pen;
    k->frame = new TupFrame();
    k->pressed = false;
    k->size = 8;
}

TupCanvas::~TupCanvas()
{
}

void TupCanvas::mousePressEvent(QMouseEvent *event)
{
    QPointF pt = mapToScene(event->pos());

    k->firstPoint = pt;
    k->path = QPainterPath();
    k->path.moveTo(k->firstPoint);
    k->oldPos = pt;

    k->pressed = true;

    k->item = new TupPathItem();
    k->item->setPen(k->pen);

    k->scene->addItem(k->item);
}

void TupCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (k->pressed) {
        QPointF lastPoint = mapToScene(event->pos());

        k->path.moveTo(k->oldPos);
        k->path.lineTo(lastPoint);

        k->item->setPath(k->path);
        k->oldPos = lastPoint;
    }
}

void TupCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (!k->item)
        return;

    QPointF pt = mapToScene(event->pos());

    if (k->firstPoint == pt && k->path.elementCount() == 1) {
        k->path.addEllipse(pt.x(), pt.y(), k->size, k->size);
    }

    smoothPath(k->path, 4);
    k->item->setPath(k->path);
    k->pressed = false;

    k->frame->addItem(k->item);
}

void TupCanvas::smoothPath(QPainterPath &path, double smoothness, int from, int to)
{
    QPolygonF pol;
    QList<QPolygonF> polygons = path.toSubpathPolygons();

    QList<QPolygonF>::iterator it = polygons.begin();

    QPolygonF::iterator pointIt;

    while (it != polygons.end()) {
           pointIt = (*it).begin();

           while (pointIt <= (*it).end()-2) {
                  pol << (*pointIt);
                  pointIt += 2;
           }
           ++it;
    }

    if (smoothness > 0) {
        path = TupGraphicalAlgorithm::bezierFit(pol, smoothness, from, to);
    } else {
        path = QPainterPath();
        path.addPolygon(pol);
    }
}

TupFrame * TupCanvas::frame()
{
    return k->frame;
}

void TupCanvas::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);
    painter->save();

    bool hasAntialiasing = painter->renderHints() & QPainter::Antialiasing;

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(QColor(0, 0, 0, 80), 1));
    
    QRectF area = QRectF(QPointF(0, 0), QSize(520, 380));
    painter->drawRect(area);

    painter->setRenderHint(QPainter::Antialiasing, hasAntialiasing);
    painter->restore();
}

void TupCanvas::updatePenSize(int width)
{
    k->pen.setWidth(width);
}

