#include "treatmentform.h"
#include <QtSql>
#include "numprefix.h"
#include "fordelete.h"

TreatmentForm::TreatmentForm(QString id, QWidget *parent, bool onlyForRead) :
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
    editCost = new LineEdit;
    QRegExp regCost("^([1-9][0-9]*|0)(\\.|,)[0-9]{2}");
    editCost->setValidator(new QRegExpValidator(regCost,this));

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
        query.prepare("SELECT treatmentname, cost FROM treatment WHERE treatmentid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editName->setText(query.value(0).toString());
            double tt = query.value(1).toDouble();
            editCost->setText(QString::number(tt,'f',2));
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

    setWindowTitle(tr("Treatment"));

    exchangeFile.setFileName("exchange.txt");
    if(!exchangeFile.isOpen()){
        exchangeFile.open(QIODevice::ReadWrite);
    }
}

void TreatmentForm::editRecord()
{
    if(!editName->text().isEmpty()){
        QTextStream stream(&exchangeFile);
        QString line;
        while(!stream.atEnd()){
            stream.readLine();
        }
        if(indexTemp != ""){
            QSqlQuery query;
            query.prepare("UPDATE treatment SET treatmentname = :name, cost = :cost"
                          " WHERE treatmentid = :id");
            query.bindValue(":name",editName->text());
            query.bindValue(":cost",editCost->text());
            query.bindValue(":id",indexTemp);
            query.exec();
            line += "UPDATE treatment SET treatmentname = '";
            line += editName->text().toUtf8();
            line += "', cost = '";
            line += editCost->text();
            line += "' WHERE treatmentid = '";
            line += indexTemp;
            line += "'";
            line += "\r\n";
            stream<<line;
        }else{
            QSqlQuery query;
            query.prepare("SELECT * FROM treatment WHERE treatmentname = :name");
            query.bindValue(":name",editName->text().simplified());
            query.exec();
            query.next();
            if(!query.isValid()){
                NumPrefix numPrefix(this);
                indexTemp = numPrefix.getPrefix("treatment");
                if(indexTemp == ""){
                    close();
                }else{
                    QSqlQuery query;
                    query.prepare("INSERT INTO treatment (treatmentid, treatmentname, cost) "
                                  "VALUES(:id, :name, :cost)");
                    query.bindValue(":id",indexTemp);
                    query.bindValue(":name",editName->text().simplified());
                    query.bindValue(":cost",editCost->text());
                    query.exec();
                    line += "INSERT INTO treatment (treatmentid, treatmentname) VALUES('";
                    line += indexTemp;
                    line += "', '";
                    line += editName->text().toUtf8();
                    line += "', cost = '";
                    line += editCost->text();
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
    }else{
        QMessageBox::warning(this,QObject::tr("Attention!!!"),tr("Name don't be empty!"));
    }
}

void TreatmentForm::deleteRecord()
{
    ForDelete forDelete(indexTemp,"treatment",this);
    forDelete.result();
    forDelete.deleteOnDefault();
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM treatment WHERE treatmentid = :id");
    query.bindValue(":id",indexTemp);
    query.exec();
    query.next();
    line += "DELETE FROM treatment WHERE treatmentid = '";
    line += indexTemp;
    line += "'";
    line += "\r\n";
    stream<<line;
}

void TreatmentForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void TreatmentForm::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("Treatment").toByteArray());
}

void TreatmentForm::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("Treatment", saveGeometry());
}
