#include "employeeform.h"
#include <QtSql>
#include "numprefix.h"
#include "fordelete.h"
#include "subdivisionform.h"
#include "postform.h"

EmployeeForm::EmployeeForm(QString id, QWidget *parent, bool onlyForRead) :
    QDialog(parent)
{
    QString styleToolButton = "QToolButton {"
                              "border: 1px solid black;"
                              "max-height: 18px;"
                              "max-width: 18px;"
                              "min-height: 18px;"
                              "min-width: 18px;"
                              "padding: 1px;"
                              "border-top-right-radius: 5px;"
                              "border-top-left-radius: 5px;"
                              "border-bottom-right-radius: 5px;"
                              "border-bottom-left-radius: 5px;"
                              "background-color: "
                              "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                              "stop:0 #d3d3d3,"
                              "stop:0.5 #bebebe,"
                              "stop:0.51 #bebebe,"
                              "stop:1 #848484);"
                              "color: #231A4C;"
                              "font: bold}"

                              "QToolButton:hover {background-color: "
                              "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                              "stop:0 #cfcccc,"
                              "stop:0.5 #333232,"
                              "stop:0.51 #000000,"
                              "stop:1 #585c5f);"
                              "color: #00cc00}";

    readSettings();
    indexTemp = id;

    labelFIO = new QLabel(tr("FIO:"));
    editFIO = new LineEdit;
    editFIO->setReadOnly(onlyForRead);
    QRegExp regExp("[\\x0410-\\x044f 0-9 \" -]{150}");
    editFIO->setValidator(new QRegExpValidator(regExp,this));
    labelFIO->setBuddy(editFIO);

    labelSub = new QLabel(tr("Subdivision:"));
    editSub = new LineEdit;
    editSub->setValidator(new QRegExpValidator(regExp,this));
    QSqlQueryModel *subModel = new QSqlQueryModel;
    subModel->setQuery("SELECT subdivisionname FROM subdivision");
    QCompleter *subComplieter = new QCompleter(subModel);
    subComplieter->setCompletionMode(QCompleter::InlineCompletion);
    subComplieter->setCompletionMode(QCompleter::PopupCompletion);
    subComplieter->setCaseSensitivity(Qt::CaseInsensitive);
    editSub->setCompleter(subComplieter);
    QToolButton *addSubButton = new QToolButton;
    QPixmap addPix(":/add.png");
    addSubButton->setIcon(addPix);
    addSubButton->setToolTip(tr("Add new Subdivision"));
    addSubButton->setStyleSheet(styleToolButton);
    connect(addSubButton,SIGNAL(clicked()),this,SLOT(addSubRecord()));
    QToolButton *seeSubButton = new QToolButton;
    QPixmap seePix(":/see.png");
    seeSubButton->setIcon(seePix);
    seeSubButton->setToolTip(tr("See this Subdivision"));
    seeSubButton->setStyleSheet(styleToolButton);
    connect(seeSubButton,SIGNAL(clicked()),this,SLOT(seeSubRecord()));
    QToolButton *listSubButton = new QToolButton;
    QPixmap listPix(":/list.png");
    listSubButton->setIcon(listPix);
    listSubButton->setToolTip(tr("List of Subdivisions"));
    listSubButton->setStyleSheet(styleToolButton);
    connect(listSubButton,SIGNAL(clicked()),this,SLOT(listSubRecord()));
    QHBoxLayout *subLayout = new QHBoxLayout;
    subLayout->addWidget(editSub);
    subLayout->addWidget(addSubButton);
    subLayout->addWidget(seeSubButton);
    subLayout->addWidget(listSubButton);
    subLayout->addStretch();

    labelPost = new QLabel(tr("Post:"));
    editPost = new LineEdit;
    editPost->setValidator(new QRegExpValidator(regExp,this));
    QSqlQueryModel *postModel = new QSqlQueryModel;
    postModel->setQuery("SELECT postname FROM post");
    QCompleter *postComplieter = new QCompleter(postModel);
    postComplieter->setCompletionMode(QCompleter::InlineCompletion);
    postComplieter->setCompletionMode(QCompleter::PopupCompletion);
    postComplieter->setCaseSensitivity(Qt::CaseInsensitive);
    editPost->setCompleter(postComplieter);
    QToolButton *addPostButton = new QToolButton;
    addPostButton->setIcon(addPix);
    addPostButton->setToolTip(tr("Add new Post"));
    addPostButton->setStyleSheet(styleToolButton);
    connect(addPostButton,SIGNAL(clicked()),this,SLOT(addPostRecord()));
    QToolButton *seePostButton = new QToolButton;
    seePostButton->setIcon(seePix);
    seePostButton->setToolTip(tr("See this Subdivision"));
    seePostButton->setStyleSheet(styleToolButton);
    connect(seePostButton,SIGNAL(clicked()),this,SLOT(seePostRecord()));
    QToolButton *listPostButton = new QToolButton;
    listPostButton->setIcon(listPix);
    listPostButton->setToolTip(tr("List of Posts"));
    listPostButton->setStyleSheet(styleToolButton);
    connect(listPostButton,SIGNAL(clicked()),this,SLOT(listPostRecord()));
    QHBoxLayout *postLayout = new QHBoxLayout;
    postLayout->addWidget(editPost);
    postLayout->addWidget(addPostButton);
    postLayout->addWidget(seePostButton);
    postLayout->addWidget(listPostButton);
    postLayout->addStretch();

    labelDate = new QLabel(tr("Birthday:"));
    editDate = new QDateEdit;

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
        query.prepare("SELECT emp.employeename, "
                      "(SELECT sub.subdivisionname FROM subdivision AS sub WHERE sub.subdivisionid = emp.subdivisionid), "
                      "(SELECT pos.postname FROM post AS pos WHERE pos.postid = emp.postid), "
                      "birthday FROM employee AS emp WHERE emp.employeeid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editFIO->setText(query.value(0).toString());
            editSub->setText(query.value(1).toString());
            editPost->setText(query.value(2).toString());
            editDate->setDate(query.value(3).toDate());
        }
    }else{
        editFIO->clear();
        editSub->clear();
        editPost->clear();
        editDate->clear();
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelFIO,0,0);
    mainLayout->addWidget(editFIO,0,1);
    mainLayout->addWidget(labelSub,1,0);
    mainLayout->addLayout(subLayout,1,1);
    mainLayout->addWidget(labelPost,2,0);
    mainLayout->addLayout(postLayout,2,1);
    mainLayout->addWidget(labelDate,3,0);
    mainLayout->addWidget(editDate,3,1);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,4,1);
        editFIO->selectAll();
    }

    setLayout(mainLayout);

    setWindowTitle(tr("Employee"));

    exchangeFile.setFileName("exchange.txt");
    if(!exchangeFile.isOpen()){
        exchangeFile.open(QIODevice::ReadWrite);
    }
}

void EmployeeForm::editRecord()
{
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    if(indexTemp != ""){
        QSqlQuery query;
        query.prepare("UPDATE employee SET employeename = :name, "
                      "subdivisionid = (SELECT subdivisionid FROM subdivision WHERE subdivisionname = :subname), "
                      "postid = (SELECT postid FROM post WHERE postname = :postname), "
                      "birthday = :date"
                      " WHERE employeeid = :id");
        query.bindValue(":name",editFIO->text());
        query.bindValue(":id",indexTemp);
        query.bindValue(":subname",editSub->text());
        query.bindValue(":postname",editPost->text());
        query.bindValue(":date",editDate->date());
        query.exec();
        line += "UPDATE employee SET employeename = '";
        line += editFIO->text().toUtf8();
        line += "', subdivisionid = (SELECT subdivisionid FROM subdivision WHERE subdivisionname = '";
        line += editSub->text().toUtf8();
        line += "'), postid = (SELECT postid FROM post WHERE postname = '";
        line += editPost->text().toUtf8();
        line += "'), birthday = '";
        line += editDate->date().toString();
        line += "' WHERE employeeid = '";
        line += indexTemp;
        line += "'";
        line += "\r\n";
        stream<<line;
    }else{
        QSqlQuery query;
        query.prepare("SELECT * FROM employee WHERE employeename = :name AND birthday = :date");
        query.bindValue(":name",editFIO->text().simplified());
        query.bindValue(":date",editDate->date());
        query.exec();
        query.next();
        if(!query.isValid()){
            NumPrefix numPrefix(this);
            indexTemp = numPrefix.getPrefix("employee");
            if(indexTemp == ""){
                close();
            }else{
                QSqlQuery query;
                query.prepare("INSERT INTO employee (employeeid, employeename, subdivisionid, postid, birthday) "
                              "VALUES(:id, :name, "
                              "(SELECT subdivisionid FROM subdivision WHERE subdivisionname = :subname), "
                              "(SELECT postid FROM post WHERE postname = :postname), "
                              ":date)");
                query.bindValue(":id",indexTemp);
                query.bindValue(":name",editFIO->text().simplified());
                query.bindValue(":subname",editSub->text());
                query.bindValue(":postname",editPost->text());
                query.bindValue(":date",editDate->date());
                query.exec();
                line += "INSERT INTO employee  (employeeid, employeename, subdivisionid, postid, birthday) VALUES('";
                line += indexTemp;
                line += "', '";
                line += editFIO->text().toUtf8();
                line += "', (SELECT subdivisionid FROM subdivision WHERE subdivisionname = '";
                line += editSub->text().toUtf8();
                line += "'), (SELECT postid FROM post WHERE postname = '";
                line += editPost->text().toUtf8();
                line += "'), ";
                line += editDate->date().toString();
                line += "')";
                line += "\r\n";
                stream<<line;
            }
        }else{
            QString tempString = editFIO->text();
            tempString += QObject::tr(" is availble!");
            QMessageBox::warning(this,QObject::tr("Attention!!!"),tempString);
        }
    }
    emit accept();
    close();
}

void EmployeeForm::deleteRecord()
{
    ForDelete forDelete(indexTemp,"employee",this);
    forDelete.result();
    forDelete.deleteOnDefault();
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM employee WHERE employeeid = :id");
    query.bindValue(":id",indexTemp);
    query.exec();
    query.next();
    line += "DELETE FROM employee WHERE employeeid = '";
    line += indexTemp;
    line += "'";
    line += "\r\n";
    stream<<line;
}

void EmployeeForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void EmployeeForm::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("Employee").toByteArray());
}

void EmployeeForm::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("Employee", saveGeometry());
}

void EmployeeForm::addSubRecord()
{
    SubdivisionForm openForm("",this,false);
    openForm.exec();
    if(openForm.rowOut() != ""){
        QSqlQuery query;
        query.prepare("SELECT subdivisionname FROM subdivision WHERE subdivisionid = :id");
        query.bindValue(":id",openForm.rowOut());
        query.exec();
        query.next();
        editSub->setText(query.value(0).toString());
    }
}

void EmployeeForm::seeSubRecord()
{

}

void EmployeeForm::listSubRecord()
{

}

void EmployeeForm::addPostRecord()
{
    PostForm openForm("",this,false);
    openForm.exec();
    if(openForm.rowOut() != ""){
        QSqlQuery query;
        query.prepare("SELECT postname FROM post WHERE postid = :posid");
        query.bindValue(":posid",openForm.rowOut());
        query.exec();
        query.next();
        editPost->setText(query.value(0).toString());
    }
}

void EmployeeForm::seePostRecord()
{
    QSqlQuery query;
    query.prepare("SELECT postid FROM post WHERE postname = :name");
    query.bindValue(":name",editPost->text());
    query.exec();
    while(query.next()){
        PostForm postForm(query.value(0).toString(),this,true);
        postForm.exec();
    }
}

void EmployeeForm::listPostRecord()
{
    QSqlQuery query;
    query.prepare("SELECT postid FROM post WHERE postname = :name");
    query.bindValue(":name",editPost->text());
    query.exec();
    query.next();
//    ViewListTable listTemp(query.value(0).toString(),"post",this);
//    listTemp.exec();
//    if(listTemp.rowOut() != ""){
//        QSqlQuery query;
//        query.prepare("SELECT postname FROM post WHERE postid = :postid");
//        query.bindValue(":postid",listTemp.rowOut());
//        query.exec();
//        query.next();
//        editPost->setText(query.value(0).toString());
//    }
}
