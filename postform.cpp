#include "postform.h"
#include <QtSql>
#include "numprefix.h"
#include "fordelete.h"

PostForm::PostForm(QString id, QWidget *parent, bool onlyForRead) :
    QDialog(parent)
{
    readSettings();
    indexTemp = id;

    labelName = new QLabel(tr("Name:"));
    editName = new LineEdit;
    editName->setReadOnly(onlyForRead);
    QRegExp regExp("[\\x0410-\\x044f 0-9 \" -]{150}");
    editName->setValidator(new QRegExpValidator(regExp,this));
    labelName->setBuddy(editName);

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
        query.prepare("SELECT postname FROM post WHERE postid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editName->setText(query.value(0).toString());
        }
    }else{
        editName->clear();
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelName,0,0);
    mainLayout->addWidget(editName,0,1);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,1,1);
        editName->selectAll();
    }

    setLayout(mainLayout);

    setWindowTitle(tr("Post"));

    exchangeFile.setFileName("exchange.txt");
    if(!exchangeFile.isOpen()){
        exchangeFile.open(QIODevice::ReadWrite);
    }
}

void PostForm::editRecord()
{
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    if(indexTemp != ""){
        QSqlQuery query;
        query.prepare("UPDATE post SET postname = :name"
                      " WHERE postid = :id");
        query.bindValue(":name",editName->text());
        query.bindValue(":id",indexTemp);
        query.exec();
        line += "UPDATE post SET postname = '";
        line += editName->text().toUtf8();
        line += "' WHERE postid = '";
        line += indexTemp;
        line += "'";
        line += "\r\n";
        stream<<line;
    }else{
        QSqlQuery query;
        query.prepare("SELECT * FROM post WHERE postname = :name");
        query.bindValue(":name",editName->text().simplified());
        query.exec();
        query.next();
        if(!query.isValid()){
            NumPrefix numPrefix(this);
            indexTemp = numPrefix.getPrefix("post");
            if(indexTemp == ""){
                close();
            }else{
                QSqlQuery query;
                query.prepare("INSERT INTO post (postid, postname) "
                              "VALUES(:id, :name)");
                query.bindValue(":id",indexTemp);
                query.bindValue(":name",editName->text().simplified());
                query.exec();
                line += "INSERT INTO post (postid, postname) VALUES('";
                line += indexTemp;
                line += "', '";
                line += editName->text().toUtf8();
                line += "')";
                line += "\r\n";
                stream<<line;
            }
        }else{
            QString tempString = editName->text();
            tempString += QObject::tr(" is availble!");
            QMessageBox::warning(this,QObject::tr("Attention!!!"),tempString);
        }
    }
    emit accept();
    close();
}

void PostForm::deleteRecord()
{
    ForDelete forDelete(indexTemp,"post",this);
    forDelete.result();
    forDelete.deleteOnDefault();
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM post WHERE postid = :id");
    query.bindValue(":id",indexTemp);
    query.exec();
    query.next();
    line += "DELETE FROM post WHERE postid = '";
    line += indexTemp;
    line += "'";
    line += "\r\n";
    stream<<line;
}

void PostForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void PostForm::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("Post").toByteArray());
}

void PostForm::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("Post", saveGeometry());
}
