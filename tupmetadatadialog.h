#ifndef TUPMETADATADIALOG_H
#define TUPMETADATADIALOG_H

#include <QDialog>

class TupMetadataDialog : public QDialog
{
    Q_OBJECT

    public:
        TupMetadataDialog(const QString &title, const QString &topics, const QString &description, QWidget *parent=0);
        ~TupMetadataDialog();
        QString imageTitle() const;
        QString imageTopics() const;
        QString imageDescription() const;

    private slots:
        void resetTitleColor(const QString &);
        void resetTopicColor(const QString &);

    private:
        struct Private;
        Private *const k;
};

#endif
