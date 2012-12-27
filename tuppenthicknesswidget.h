#ifndef TUPPENTHICKNESSWIDGET_H
#define TUPPENTHICKNESSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QSize>

class TupPenThicknessWidget : public QWidget
{
    Q_OBJECT

    public:
        TupPenThicknessWidget(QWidget *parent = 0);
        ~TupPenThicknessWidget();

        QSize minimumSizeHint() const;
        QSize sizeHint() const;
        void setColor(const QColor color);
        void setBrush(int index);
        void setBrush(const QBrush brush);
        void setOpacity(double opacity);

    public slots:
        void render(int thickness);
        void render(double thickness);
        
    protected:
        void paintEvent(QPaintEvent *e);
   
    private:
        struct Private;
        Private *const k;
};

#endif
