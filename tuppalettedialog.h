#ifndef TUPPALETTEDIALOG_H
#define TUPPALETTEDIALOG_H

#include <QDialog>

class TupPaletteDialog : public QDialog
{
    Q_OBJECT

    public:
        TupPaletteDialog(const QColor color, QWidget *parent);
        ~TupPaletteDialog();

    signals:
        void updateColor(const QColor color);

    private:
        void setColorsArray();
        struct Private;
        Private *const k;
};

#endif
