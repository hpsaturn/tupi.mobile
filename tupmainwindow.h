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
        void resizeEvent ( QResizeEvent * event );

    private:
        void setToolBar();
        void setCanvas();

        struct Private;
        Private *const k;

    private slots:
        void postIt();
        void showURLDialog(const QString &message);
        void penDialog();
        void updatePenSize(int width);
};

#endif
