#ifndef PUTFILE_H
#define PUTFILE_H

#include <QtWidgets>
#include <QtNetwork>

class PutFile : public QDialog
{
    Q_OBJECT

public:
    PutFile(QWidget *);

public slots:
    bool putFile(QString);

private slots:
    void updateDataTransferProgress(qint64,qint64);
    void closeFile();

private:
    QFile *filePut;
    QProgressDialog *progressDialog;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
};

#endif // PUTFILE_H
