#include "exchangeform.h"
#include <QtSql>
#include "putfile.h"

ExchangeForm::ExchangeForm(QWidget *parent) : QDialog(parent)
{
    exchangeButton = new QPushButton(tr("Exchange"));
    connect(exchangeButton,SIGNAL(clicked()),this,SLOT(readExchanges()));
    exchangeButton->setDefault(true);

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(exchangeButton,QDialogButtonBox::ActionRole);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(buttonBox,0,0);
    setLayout(mainLayout);
    setWindowTitle(tr("Exchange Data Base"));
}

void ExchangeForm::readExchanges()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    QString nameThisNode = settings.value("numprefix").toString();
    QSqlQuery query;
    query.exec("SELECT nodecode FROM node");
    while(query.next()){
        QString fileNameToFTP;
        if(nameThisNode != query.value(0).toString()){
            fileNameToFTP = "Message_";
            fileNameToFTP += query.value(0).toString();
            fileNameToFTP += "_";
            fileNameToFTP += nameThisNode;
            fileNameToFTP += ".txt";
            QFile exchangeFile("./exchange.txt");
            exchangeFile.open(QIODevice::ReadOnly);
            if(exchangeFile.size() != 0){
                exchangeFile.copy(fileNameToFTP);
                exchangeFile.close();

                QString name = "ftp://";
                name += "91.102.219.74";
                name += "/QtProject/Yarn/Exchange/"; //Yarn.dat";
                name += fileNameToFTP;
                PutFile pFile(this);
                bool str = pFile.putFile(fileNameToFTP);
                qDebug()<<str;
                if(str == false){
                    QFile toDel(fileNameToFTP);
                    toDel.remove();
                    settings.setValue("Send",true);
                }
            }
        }
    }
}

void ExchangeForm::writeExchanges()
{

}
