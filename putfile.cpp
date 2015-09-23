#include "putfile.h"

PutFile::PutFile(QWidget *parent) : QDialog(parent)
{
}

bool PutFile::putFile(QString fileToSend)
{
    filePut = new QFile(fileToSend);
    if(!filePut->open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("Attention!"),
                             tr("Don't Open File!"));
        close();
    }

    QString name = "ftp://";
    name += "91.102.219.74";
    name += "/QtProject/MSO/Exchange/";
    name += fileToSend;

    progressDialog = new QProgressDialog(this);
    progressDialog->setLabelText(tr("Put File to Server..."));
    progressDialog->setEnabled(true);
    progressDialog->show();

    QUrl url(name);
    url.setUserName("ftpsites");
    url.setPassword("Andrew123");
    url.setPort(2210);

    QEventLoop loop;
    manager = new QNetworkAccessManager(0);
    reply = manager->put(QNetworkRequest(url),filePut);
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    connect(reply,SIGNAL(finished()),this,SLOT(closeFile()));
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateDataTransferProgress(qint64,qint64)));
    loop.exec();
    return reply->error();
}

void PutFile::updateDataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(readBytes);
}

void PutFile::closeFile()
{
    filePut->close();
    emit close();
}
