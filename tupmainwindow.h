#ifndef TUPMAINWINDOW_H
#define TUPMAINWINDOW_H

#include <QMainWindow>

class TupMainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        TupMainWindow();
        ~TupMainWindow(); 

    protected:
        void closeEvent(QCloseEvent *event);
        void resizeEvent(QResizeEvent *event);

    private:
        void setToolBar();
        void setCanvas();

        struct Private;
        Private *const k;

    private slots:
        void postIt();
        void showURLDialog(const QString &url);
        void penWidthDialog();
        void colorDialog();
        void opacityDialog();
        void brushDialog();

        void updatePenWidth(int width);
        void updatePenColor(const QColor color);
        void updatePenOpacity(double opacity);
        void updatePenBrush(Qt::BrushStyle style);

        void undo();
        void redo();
        void newCanvas();
};

#endif
