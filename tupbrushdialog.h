#ifndef TUPBRUSHDIALOG_H
#define TUPBRUSHDIALOG_H

#include <QDialog>
#include <QPen>

class TupBrushDialog : public QDialog
{
    Q_OBJECT

    public:
        TupBrushDialog(const QPen pen, QWidget *parent);
        ~TupBrushDialog();

    signals:
        void updatePenBrush(Qt::BrushStyle brushStyle);

    private slots:
        void updateSelection(int index);
        void closeDialog();

    private:
        void setBrushOptions();
        struct Private;
        Private *const k;
};

#endif
