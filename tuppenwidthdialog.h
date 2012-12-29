#ifndef TUPPENWIDTHDIALOG_H
#define TUPPENWIDTHDIALOG_H

#include <QDialog>

class TupPenWidthDialog : public QDialog
{
    Q_OBJECT

    public:
        TupPenWidthDialog(const QPen pen, QWidget *parent);
        ~TupPenWidthDialog();

    signals:
        void updatePen(int width);

    private slots:
        void fivePointsLess();
        void onePointLess();
        void onePointMore();
        void fivePointsMore();

    private:
        void setBrushCanvas();
        void setLabelPanel();
        void setButtonsPanel();
        void modifySize(int value);

        struct Private;
        Private *const k;
};

#endif
