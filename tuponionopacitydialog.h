#ifndef TUPONIONOPACITYDIALOG_H
#define TUPONIONOPACITYDIALOG_H

#include <QDialog>
#include <QColor>

class TupOnionOpacityDialog : public QDialog
{
    Q_OBJECT

    public:
        TupOnionOpacityDialog(const QColor &color, double opacity, QWidget *parent);
        ~TupOnionOpacityDialog();

    signals:
        void updateOpacity(double);

    private slots:
        void fivePointsLess();
        void onePointLess();
        void onePointMore();
        void fivePointsMore();

    private:
        void setOpacityCanvas();
        void setButtonsPanel();
        void modifySize(double value);

        struct Private;
        Private *const k;
};

#endif
