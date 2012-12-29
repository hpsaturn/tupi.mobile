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
   QList<TupPathItem *> undoList;

   QPainterPath path;
   QPointF firstPoint;
   QPointF oldPos;
   QPen pen;
   int size;
   double opacity;

   bool pressed;
};

TupCanvas::TupCanvas(QGraphicsScene *scene, const QPen pen, double opacity, QWidget *parent) : QGraphicsView(scene, parent), k(new Private)
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
    k->opacity = opacity;
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
    QColor color = k->pen.color();
    color.setAlpha(alphaValue(k->opacity));
    k->pen.setColor(color);
    k->item->setPen(k->pen);
    // k->item->setOpacity(k->opacity);

    k->scene->addItem(k->item);
}

int TupCanvas::alphaValue(double opacity)
{
    double alpha = 255 * opacity;
    int value = (int) alpha;
    return value;
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
    
    QRectF area = k->scene->sceneRect();

    painter->drawRect(area);

    painter->setRenderHint(QPainter::Antialiasing, hasAntialiasing);
    painter->restore();
}

void TupCanvas::updatePenSize(int width)
{
    k->pen.setWidth(width);
}

void TupCanvas::updateColor(const QColor color)
{
    k->pen.setColor(color);
}

void TupCanvas::updatePenOpacity(double opacity)
{
    k->opacity = opacity;
}

void TupCanvas::undo()
{
    int index = k->scene->items().count();
    if (index > 0) {
        TupPathItem *item = (TupPathItem *) k->frame->takeItem(index - 1);
        k->scene->removeItem(item);
        k->undoList.append(item);
    }
}

void TupCanvas::redo()
{
    int index = k->undoList.size();
    if (k->undoList.size() > 0) {
        TupPathItem *item = (TupPathItem *) k->undoList.takeAt(index - 1);
        k->scene->addItem(item);
        k->frame->addItem(item);
    }
}

void TupCanvas::clear()
{
    k->scene->clear();
    k->frame->clear();
    k->undoList.clear();
}
