#include "putbase.h"

PutBase::PutBase(QWidget *parent) : QDialog(parent)
{
}

void PutBase::putBase()
{
    filePut = new QFile("./MSO.dat");
    if(!filePut->open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("Attention!"),
                             tr("Don't Open DataBase File!"));
        return;
    }

    QString name = "ftp://";
    name += "91.102.219.74";
    name += "/QtProject/MSO/Base/MSO.dat";

    progressDialog = new QProgressDialog(this);
    progressDialog->setLabelText(tr("Put DataBase to Server..."));
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
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateDataTransferProgress(qint64,qint64)));
    loop.exec();
}

void PutBase::updateDataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(readBytes);
}
