#ifndef TUPPENPREVIEWCANVAS_H
#define TUPPENPREVIEWCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QSize>

class TupPenPreviewCanvas : public QWidget
{
    Q_OBJECT

    public:
        TupPenPreviewCanvas(QPen pen, double opacity, QWidget *parent = 0);
        ~TupPenPreviewCanvas();

        QSize minimumSizeHint() const;
        QSize sizeHint() const;

    public slots:
        void render(int width);
        void render(double opacity);
        
    protected:
        void paintEvent(QPaintEvent *e);
   
    private:
        struct Private;
        Private *const k;
};

#endif
