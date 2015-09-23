#include "getfile.h"

GetFile::GetFile(QWidget *parent) : QDialog(parent)
{
}

void GetFile::getFileHttp()
{
    progressDialog = new QProgressDialog(this);
    fileHttp = new QFile("Yarn.dat");
    fileHttp->open(QIODevice::WriteOnly);
    url = "http://91.102.219.74/QtProject/Yarn/Base/Yarn.dat";
    //url = "http://91.102.219.74/QtProject/Yarn/Yarn.exe";

    reply = http.get(QNetworkRequest(url));
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(httpDone()));

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,
            SLOT(updateDataReadProgress(qint64,qint64)));
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,
            SLOT(updateDataReadProgress(qint64,qint64)));

    progressDialog->setLabelText(tr("Downloading DataBase ..."));
    progressDialog->setEnabled(true);
    progressDialog->exec();
}

void GetFile::httpDone()
{
    fileHttp->close();
    closeConnection();
}

void GetFile::updateDataReadProgress(qint64 readBytes, qint64 totalBytes)
{
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(readBytes);
}

void GetFile::httpReadyRead()
{
    if(fileHttp)
        fileHttp->write(reply->readAll());

}

void GetFile::closeConnection()
{
    progressDialog->hide();
    http.destroyed();
}
