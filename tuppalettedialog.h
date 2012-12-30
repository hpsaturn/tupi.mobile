#ifndef TUPPALETTEDIALOG_H
#define TUPPALETTEDIALOG_H

#include <QDialog>

class TupPaletteDialog : public QDialog
{
    Q_OBJECT

    public:
        TupPaletteDialog(const QBrush brush, const QSize size, QWidget *parent);
        ~TupPaletteDialog();

    signals:
        void updateColor(const QColor color);

    private slots:
        void updateMatrix(int index);
        void closeDialog();

    private:
        void setColorsArray();
        struct Private;
        Private *const k;
};

#endif
