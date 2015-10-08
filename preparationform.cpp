#include "preparationform.h"
#include <QtSql>
#include "numprefix.h"
#include "fordelete.h"

PreparationForm::PreparationForm(QString id, QWidget *parent, bool onlyForRead) :
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

    labelExpirationDate = new QLabel(tr("Expiration Date:"));
    editExpirationDate = new QDateEdit;

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
        query.prepare("SELECT preparationname, cost, expirationdate FROM preparation WHERE preparationid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editName->setText(query.value(0).toString());
            double tt = query.value(1).toDouble();
            editCost->setText(QString::number(tt,'f',2));
            editExpirationDate->setDate(query.value(2).toDate());
        }
    }else{
        editName->clear();
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelName,0,0);
    mainLayout->addWidget(editName,0,1);
    mainLayout->addWidget(labelCost,1,0);
    mainLayout->addWidget(editCost,1,1);
    mainLayout->addWidget(labelExpirationDate,2,0);
    mainLayout->addWidget(editExpirationDate,2,1);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,3,1);
        editName->selectAll();
    }

    setLayout(mainLayout);

    setWindowTitle(tr("Preparation"));

    exchangeFile.setFileName("exchange.txt");
    if(!exchangeFile.isOpen()){
        exchangeFile.open(QIODevice::ReadWrite);
    }
}

void PreparationForm::editRecord()
{
    if(!editName->text().isEmpty()){
        QTextStream stream(&exchangeFile);
        QString line;
        while(!stream.atEnd()){
            stream.readLine();
        }
        if(indexTemp != ""){
            QSqlQuery query;
            query.prepare("UPDATE preparation SET preparationname = :name, cost = :cost, expirationdate = :date"
                          " WHERE preparationid = :id");
            query.bindValue(":name",editName->text());
            query.bindValue(":cost",editCost->text());
            query.bindValue(":id",indexTemp);
            query.bindValue(":expirationdate",editExpirationDate->date());
            query.exec();
            line += "UPDATE preparation SET preparationname = '";
            line += editName->text().toUtf8();
            line += "', cost = '";
            line += editCost->text();
            line += "', expirationdate = '";
            line += editExpirationDate->date().toString();
            line += "' WHERE preparationid = '";
            line += indexTemp;
            line += "'";
            line += "\r\n";
            stream<<line;
        }else{
            QSqlQuery query;
            query.prepare("SELECT * FROM preparation WHERE preparationname = :name");
            query.bindValue(":name",editName->text().simplified());
            query.exec();
            query.next();
            if(!query.isValid()){
                NumPrefix numPrefix(this);
                indexTemp = numPrefix.getPrefix("preparation");
                if(indexTemp == ""){
                    close();
                }else{
                    QSqlQuery query;
                    query.prepare("INSERT INTO preparation (preparationid, preparationname, cost, expirationdate) "
                                  "VALUES(:id, :name, :cost, :date)");
                    query.bindValue(":id",indexTemp);
                    query.bindValue(":name",editName->text().simplified());
                    query.bindValue(":cost",editCost->text());
                    query.bindValue(":date",editExpirationDate->date());
                    query.exec();
                    line += "INSERT INTO preparation (preparationid, preparationname, cost, expirationdate) VALUES('";
                    line += indexTemp;
                    line += "', '";
                    line += editName->text().toUtf8();
                    line += "', '";
                    line += editCost->text();
                    line += "', '";
                    line += editExpirationDate->date().toString();
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

void PreparationForm::deleteRecord()
{
    ForDelete forDelete(indexTemp,"preparation",this);
    forDelete.result();
    forDelete.deleteOnDefault();
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM preparation WHERE preparationid = :id");
    query.bindValue(":id",indexTemp);
    query.exec();
    query.next();
    line += "DELETE FROM preparation WHERE preparationid = '";
    line += indexTemp;
    line += "'";
    line += "\r\n";
    stream<<line;
}

void PreparationForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void PreparationForm::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("Preparation").toByteArray());
}

void PreparationForm::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("Preparation", saveGeometry());
}
