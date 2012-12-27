#ifndef TUPBRUSHMANAGER_H
#define TUPBRUSHMANAGER_H

#include <QObject>
#include <QPen>
#include <QBrush>

/**
 * @author David Cuadrado
*/

class TupBrushManager : public QObject
{
    Q_OBJECT

    public:
        TupBrushManager(QObject * parent = 0);
        TupBrushManager(const QPen &pen, const QBrush &brush, QObject * parent = 0);
        ~TupBrushManager();
        
        void setPen(const QPen &pen);
        void setPenColor(const QColor &color);
        void setPenSize(int size);
        QPen pen() const;
        
        void setBrush(const QBrush &brush);
        QBrush brush() const;
        
        int penWidth() const;
        QColor penColor() const;
        QBrush penBrush() const;
        
        QBrush brushColor() const;
        
    signals:
        void penChanged(const QPen &pen);
        void brushChanged(const QBrush &brush);
        
    private:
        struct Private;
        Private *const k;

};

#endif
