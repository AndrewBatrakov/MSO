#include "employeeform.h"
#include <QtSql>
#include "numprefix.h"
#include "fordelete.h"

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
        query.prepare("SELECT employeename, subdivisionid, postid, birthday FROM employee WHERE employeeid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editFIO->setText(query.value(0).toString());
            QSqlQuery querySub;
            querySub.prepare("SELECT subdivisionname FROM subdivision WHERE subdivisionid = :subid");
            querySub.bindValue(":subid",query.value(1).toString());
            querySub.exec();
            querySub.next();
            editSub->setText(querySub.value(0).toString());
            QSqlQuery queryPost;
            queryPost.prepare("SELECT postname FROM post WHERE postid = :postid");
            queryPost.bindValue(":postid",query.value(2).toString());
            queryPost.exec();
            queryPost.next();
            editPost->setText(queryPost.value(0).toString());
            editDate->setDate(query.value(3).toDate());
        }
    }else{
        editFIO->clear();
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
        query.prepare("UPDATE employee SET employeename = :name, subdivisionid = :subid, postid = :postid, birthday = :date"
                      " WHERE employeeid = :id");
        query.bindValue(":name",editFIO->text());
        query.bindValue(":id",indexTemp);
        QSqlQuery querySub;
        querySub.prepare("SELECT subdivisionid FROM subdivision WHERE subdivisionname = :subname");
        querySub.bindValue(":subname",editSub->text());
        querySub.exec();
        querySub.next();
        query.bindValue(":subid",querySub.value(0).toString());
        QSqlQuery queryPost;
        queryPost.prepare("SELECT postid FROM post WHERE postname = :postname");
        queryPost.bindValue(":postname",editPost->text());
        queryPost.exec();
        queryPost.next();
        query.bindValue(":postid",queryPost.value(0).toString());
        query.bindValue(":date",editDate->date());
        query.exec();
        line += "UPDATE employee SET employeename = '";
        line += editFIO->text().toUtf8();
        line += "', subdivisionid = '";
        line += querySub.value(0).toString();
        line += "', postid = '";
        line += queryPost.value(0).toString();
        line += "', birthday = '";
        line += editDate->date().toString();
        line += "' WHERE employeeid = '";
        line += indexTemp;
        line += "'";
        line += "\r\n";
        stream<<line;
    }else{
        QSqlQuery query;
        query.prepare("SELECT * FROM employee WHERE employeename = :name");
        query.bindValue(":name",editFIO->text().simplified());
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
                              "VALUES(:id, :name)");
                query.bindValue(":id",indexTemp);
                query.bindValue(":name",editFIO->text().simplified());
                query.exec();
                line += "INSERT INTO post (postid, postname) VALUES('";
                line += indexTemp;
                line += "', '";
                line += editFIO->text().toUtf8();
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
//    ForDelete forDelete(indexTemp,"post",this);
//    forDelete.result();
//    forDelete.deleteOnDefault();
//    QTextStream stream(&exchangeFile);
//    QString line;
//    while(!stream.atEnd()){
//        stream.readLine();
//    }
//    QSqlQuery query;
//    query.prepare("DELETE FROM post WHERE postid = :id");
//    query.bindValue(":id",indexTemp);
//    query.exec();
//    query.next();
//    line += "DELETE FROM post WHERE postid = '";
//    line += indexTemp;
//    line += "'";
//    line += "\r\n";
//    stream<<line;
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

}

void EmployeeForm::seeSubRecord()
{

}

void EmployeeForm::listSubRecord()
{

}

void EmployeeForm::addPostRecord()
{

}

void EmployeeForm::seePostRecord()
{

}

void EmployeeForm::listPostRecord()
{

}
