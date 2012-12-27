#ifndef TUPPAINTAREABASE_H
#define TUPPAINTAREABASE_H

#include <QGraphicsView>
#include <QGraphicsScene> 

#include "tupgraphicalgorithm.h"
#include "tupframe.h"

class TupCanvas : public QGraphicsView
{
    Q_OBJECT

    public:
        TupCanvas(QGraphicsScene *scene, const QPen pen, QWidget *parent);
        ~TupCanvas();
        TupFrame * frame();
        void updatePenSize(int size);

    protected:
        virtual void drawBackground(QPainter *painter, const QRectF &rect);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

    private:
        void smoothPath(QPainterPath &path, double smoothness, int from = 0, int to = -1);
        struct Private;
        Private *const k;
};

#endif
