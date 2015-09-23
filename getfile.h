#ifndef GETFILE_H
#define GETFILE_H

#include <QtWidgets>
#include <QtNetwork>

class GetFile : public QDialog
{
    Q_OBJECT

public:
    GetFile(QWidget *);

public slots:
    void getFileHttp();

private slots:
    void httpDone();
    void updateDataReadProgress(qint64,qint64);
    void httpReadyRead();

    void closeConnection();

private:
    QUrl url;
    QNetworkAccessManager http;
    QNetworkReply *reply;
    QFile *fileHttp;
    QProgressDialog *progressDialog;
};

#endif // GETFILE_H
