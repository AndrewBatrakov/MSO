#ifndef PUTBASE_H
#define PUTBASE_H

#include <QtWidgets>
#include <QtNetwork>

class PutBase : public QDialog
{
    Q_OBJECT

public:
    PutBase(QWidget *);

public slots:
    void putBase();

private slots:
    void updateDataTransferProgress(qint64,qint64);

private:
    QFile *filePut;
    QProgressDialog *progressDialog;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
};

#endif // PUTBASE_H
