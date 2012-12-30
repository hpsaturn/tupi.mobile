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
        TupCanvas(QGraphicsScene *scene, const QPen pen, double opacity, QWidget *parent);
        ~TupCanvas();
        TupFrame * frame();
        void updatePenSize(int width);
        void updatePenColor(const QColor color);
        void updatePenOpacity(double opacity);
        void updatePenBrush(Qt::BrushStyle brushStyle);

        void undo();
        void redo();
        void clear();

    protected:
        virtual void drawBackground(QPainter *painter, const QRectF &rect);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        // bool event(QEvent *event);

    private:
        void smoothPath(QPainterPath &path, double smoothness, int from = 0, int to = -1);
        int alphaValue(double opacity);

        struct Private;
        Private *const k;
};

#endif
