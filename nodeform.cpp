#include "nodeform.h"
#include <QtSql>
#include "numprefix.h"
#include "fordelete.h"

NodeForm::NodeForm(QString id, QWidget *parent, bool onlyForRead) :
    QDialog(parent)
{
    readSettings();
    indexTemp = id;

    labelCode = new QLabel(tr("Code:"));
    editCode = new LineEdit;
    editCode->setReadOnly(onlyForRead);
    QRegExp regC("[A-Z]{3}");
    editCode->setValidator(new QRegExpValidator(regC,this));
    labelCode->setBuddy(editCode);

    labelName = new QLabel(tr("Name:"));
    editName = new LineEdit;
    editName->setReadOnly(onlyForRead);
    QRegExp regExp("[\\x0410-\\x044f 0-9 \" -]{150}");
    editName->setValidator(new QRegExpValidator(regExp,this));
    labelName->setBuddy(editName);

    head = new QCheckBox;
    head->setText(tr("Head Node"));

    saveButton = new QPushButton(tr("Save"));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(editRecord()));
    saveButton->setToolTip(tr("Save And Close Button"));

    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(true);
    cancelButton->setStyleSheet("QPushButton:hover {color: red}");
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(accept()));
    cancelButton->setToolTip(tr("Cancel Button"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(cancelButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(saveButton,QDialogButtonBox::ActionRole);

    if(indexTemp != ""){
        QSqlQuery query;
        query.prepare("SELECT nodename, nodecode, head FROM node WHERE nodeid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editCode->setText(query.value(1).toString());
            editName->setText(query.value(0).toString());
            head->setChecked(query.value(2).toBool());
        }
    }else{
        editName->clear();
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelCode,0,0);
    mainLayout->addWidget(editCode,0,1);
    mainLayout->addWidget(labelName,1,0);
    mainLayout->addWidget(editName,1,1);
    mainLayout->addWidget(head,2,1);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,3,1);
        editName->selectAll();
    }

    setLayout(mainLayout);

    setWindowTitle(tr("Node"));

    exchangeFile.setFileName("exchange.txt");
    if(!exchangeFile.isOpen()){
        exchangeFile.open(QIODevice::ReadWrite);
    }
}

void NodeForm::editRecord()
{
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    if(indexTemp != ""){
        QSqlQuery query;
        query.prepare("UPDATE node SET nodename = :name, nodecode = :code, head = :head"
                      " WHERE nodeid = :id");
        query.bindValue(":name",editName->text());
        query.bindValue(":code",editCode->text());
        query.bindValue(":head",head->checkState());
        query.bindValue(":id",indexTemp);
        query.exec();
        line += "UPDATE node SET nodename = '";
        line += editName->text().toUtf8();
        line += "', nodecode = '";
        line += editCode->text().toUtf8();
        line += "', head = '";
        line += QString::number(head->checkState());
        line += "' WHERE colorid = '";
        line += indexTemp;
        line += "'";
        line += "\r\n";
        stream<<line;
    }else{
        QSqlQuery query;
        query.prepare("SELECT * FROM node WHERE nodename = :name");
        query.bindValue(":name",editName->text().simplified());
        query.exec();
        query.next();
        if(!query.isValid()){
            NumPrefix numPrefix(this);
            indexTemp = numPrefix.getPrefix("node");
            if(indexTemp == ""){
                close();
            }else{
                QSqlQuery query;
                query.prepare("INSERT INTO node (nodeid, nodename, nodecode, head) "
                              "VALUES(:id, :name, :code, :head)");
                query.bindValue(":id",indexTemp);
                query.bindValue(":name",editName->text().simplified());
                query.bindValue(":code",editCode->text());
                query.bindValue(":head",head->checkState());
                query.exec();
                line += "INSERT INTO node (nodeid, nodename, nodecode, head) VALUES('";
                line += indexTemp;
                line += "', '";
                line += editName->text().toUtf8();
                line += "', nodecode = '";
                line += editCode->text().toUtf8();
                line += "', head = '";
                line += QString::number(head->checkState());
                line += "')";
                line += "\r\n";
                stream<<line;
            }
        }else{
            QString tempString = editName->text();
            tempString += QObject::tr(" is availble!");
            QMessageBox::warning(this,QObject::tr("Atention!!!"),tempString);
        }
    }
    emit accept();
    close();
}

void NodeForm::deleteRecord()
{
    ForDelete forDelete(indexTemp,"node",this);
    forDelete.result();
    forDelete.deleteOnDefault();
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM node WHERE nodeid = :id");
    query.bindValue(":id",indexTemp);
    query.exec();
    query.next();
    line += "DELETE FROM node WHERE nodeid = '";
    line += indexTemp;
    line += "'";
    line += "\r\n";
    stream<<line;
}

void NodeForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void NodeForm::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("Node").toByteArray());
}

void NodeForm::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("Node", saveGeometry());
}
