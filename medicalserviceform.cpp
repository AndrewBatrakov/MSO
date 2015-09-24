#include "medicalserviceform.h"
#include <QtSql>
#include "numprefix.h"
#include "fordelete.h"

MedicalServiceForm::MedicalServiceForm(QString id, QWidget *parent, bool onlyForRead) :
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

    labelCost = new QLabel(tr("Cost:"));
    editCost = new QDoubleSpinBox;
    editCost->setMaximum(999999.99);
    //QRegExp regCost("^([1-9][0-9]*|0)(\\.|,)[0-9]{2}");
    //editCost->setValidator(new QRegExpValidator(regCost,this));

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
        query.prepare("SELECT medicalservicename, cost FROM medicalservice WHERE medicalserviceid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            qDebug()<<query.value(1);
            editName->setText(query.value(0).toString());
            editCost->setValue(query.value(1).toDouble());
        }
    }else{
        editName->clear();
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelName,0,0);
    mainLayout->addWidget(editName,0,1);
    mainLayout->addWidget(labelCost,1,0);
    mainLayout->addWidget(editCost,1,1);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,2,1);
        editName->selectAll();
    }

    setLayout(mainLayout);

    setWindowTitle(tr("Medical Service"));

    exchangeFile.setFileName("exchange.txt");
    if(!exchangeFile.isOpen()){
        exchangeFile.open(QIODevice::ReadWrite);
    }
}

void MedicalServiceForm::editRecord()
{
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    if(indexTemp != ""){
        QSqlQuery query;
        query.prepare("UPDATE medicalservice SET medicalservicename = :name, cost = :cost"
                      " WHERE medicalserviceid = :id");
        query.bindValue(":name",editName->text());
        query.bindValue(":cost",editCost->value());
        query.bindValue(":id",indexTemp);
        query.exec();
        line += "UPDATE medicalservice SET medicalservicename = '";
        line += editName->text().toUtf8();
        line += "', '";
        line += editCost->value();
        line += "' WHERE medicalserviceid = '";
        line += indexTemp;
        line += "'";
        line += "\r\n";
        stream<<line;
    }else{
        QSqlQuery query;
        query.prepare("SELECT * FROM medicalservice WHERE medicalservicename = :name");
        query.bindValue(":name",editName->text().simplified());
        query.exec();
        query.next();
        if(!query.isValid()){
            NumPrefix numPrefix(this);
            indexTemp = numPrefix.getPrefix("medicalservice");
            if(indexTemp == ""){
                close();
            }else{
                QSqlQuery query;
                query.prepare("INSERT INTO medicalservice (medicalserviceid, medicalservicename, cost) "
                              "VALUES(:id, :name, :cost)");
                query.bindValue(":id",indexTemp);
                query.bindValue(":name",editName->text().simplified());
                query.bindValue(":cost",editCost->value());
                query.exec();
                line += "INSERT INTO medicalservice (medicalserviceid, medicalservicename, cost) VALUES('";
                line += indexTemp;
                line += "', '";
                line += editName->text().toUtf8();
                line += "', '";
                line += editCost->value();
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

void MedicalServiceForm::deleteRecord()
{
    ForDelete forDelete(indexTemp,"medicalservice",this);
    forDelete.result();
    forDelete.deleteOnDefault();
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM medicalservice WHERE medicalserviceid = :id");
    query.bindValue(":id",indexTemp);
    query.exec();
    query.next();
    line += "DELETE FROM medicalservice WHERE medicalserviceid = '";
    line += indexTemp;
    line += "'";
    line += "\r\n";
    stream<<line;
}

void MedicalServiceForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void MedicalServiceForm::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("MedicalService").toByteArray());
}

void MedicalServiceForm::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("MedicalService", saveGeometry());
}

