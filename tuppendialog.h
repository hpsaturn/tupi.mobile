#ifndef TUPPENDIALOG_H
#define TUPPENDIALOG_H

#include "tupbrushmanager.h"
#include <QDialog>

class TupPenDialog : public QDialog
{
    Q_OBJECT

    public:
        TupPenDialog(TupBrushManager *brushManager, QWidget *parent);
        ~TupPenDialog();

        QSize sizeHint() const;

    signals:
        void updatePen(int);

    private slots:
        void fivePointsLess();
        void onePointLess();
        void onePointMore();
        void fivePointsMore();

    private:
        void setBrushCanvas();
        void setButtonsPanel();
        void modifySize(int value);

        struct Private;
        Private *const k;
};

#endif
