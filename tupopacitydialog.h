#ifndef TUPOPACITYDIALOG_H
#define TUPOPACITYDIALOG_H

#include <QDialog>
#include <QColor>

class TupOpacityDialog : public QDialog
{
    Q_OBJECT

    public:
        TupOpacityDialog(const QColor &color, double opacity, QWidget *parent);
        ~TupOpacityDialog();

    signals:
        void updateOpacity(double);

    private slots:
        void fivePointsLess();
        void onePointLess();
        void onePointMore();
        void fivePointsMore();

    private:
        void setOpacityCanvas();
        void setLabelPanel();
        void setButtonsPanel();
        void modifySize(double value);

        struct Private;
        Private *const k;
};

#endif
