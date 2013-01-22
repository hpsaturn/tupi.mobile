#ifndef TUPURLDIALOG_H
#define TUPURLDIALOG_H

#include <QDialog>

class TupUrlDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit TupUrlDialog(const QString &url, QWidget *parent = 0);
};

#endif
