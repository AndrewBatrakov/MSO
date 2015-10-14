#include "treatmentdocform.h"
#include <QtSql>
#include "fordelete.h"
#include "numprefix.h"

TreatmentDocForm::TreatmentDocForm(QString id, QWidget *parent, bool onlyForRead) : QDialog(parent)
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

    labelNumberDoc = new QLabel(tr("Number:"));
    editNumberDoc = new LineEdit;
    editNumberDoc->setReadOnly(true);
    labelNumberDoc->setBuddy(editNumberDoc);

    labelDateDoc = new QLabel(tr("Date:"));
    editDateDoc = new QDateEdit;
    labelDateDoc->setBuddy(editDateDoc);
    editDateDoc->setCalendarPopup(true);
    editDateDoc->setDate(QDate::currentDate());


    labelFIO = new QLabel(tr("FIO:"));
    editFIO = new LineEdit;
    editFIO->setReadOnly(onlyForRead);
    QRegExp regExp("[\\x0410-\\x044f 0-9 \" -]{150}");
    editFIO->setValidator(new QRegExpValidator(regExp,this));
    labelFIO->setBuddy(editFIO);

    QSqlQueryModel *empModel = new QSqlQueryModel;
    empModel->setQuery("SELECT employeename FROM employee");
    QCompleter *empComplieter = new QCompleter(empModel);
    empComplieter->setCompletionMode(QCompleter::InlineCompletion);
    empComplieter->setCompletionMode(QCompleter::PopupCompletion);
    empComplieter->setCaseSensitivity(Qt::CaseInsensitive);
    editFIO->setCompleter(empComplieter);
    QToolButton *addEmpButton = new QToolButton;
    QPixmap addPix(":/add.png");
    addEmpButton->setIcon(addPix);
    addEmpButton->setToolTip(tr("Add new Employee"));
    addEmpButton->setStyleSheet(styleToolButton);
    connect(addEmpButton,SIGNAL(clicked()),this,SLOT(addEmpRecord()));
    QToolButton *seeEmpButton = new QToolButton;
    QPixmap seePix(":/see.png");
    seeEmpButton->setIcon(seePix);
    seeEmpButton->setToolTip(tr("See this Employee"));
    seeEmpButton->setStyleSheet(styleToolButton);
    connect(seeEmpButton,SIGNAL(clicked()),this,SLOT(seeEmpRecord()));
    QToolButton *listEmpButton = new QToolButton;
    QPixmap listPix(":/list.png");
    listEmpButton->setIcon(listPix);
    listEmpButton->setToolTip(tr("List of Emmployees"));
    listEmpButton->setStyleSheet(styleToolButton);
    connect(listEmpButton,SIGNAL(clicked()),this,SLOT(listEmpRecord()));
    QHBoxLayout *empLayout = new QHBoxLayout;
    empLayout->addWidget(editFIO);
    empLayout->addWidget(addEmpButton);
    empLayout->addWidget(seeEmpButton);
    empLayout->addWidget(listEmpButton);
    empLayout->addStretch();
    connect(editFIO,SIGNAL(textChanged(QString)),this,SLOT(fioChange()));

    labelOrg = new QLabel(tr("Organization:"));
    editOrg = new LineEdit;
    editOrg->setReadOnly(true);
    labelOrg->setBuddy(editOrg);

    labelSub = new QLabel(tr("Subdivision:"));
    editSub = new LineEdit;
    editSub->setReadOnly(true);
    labelSub->setBuddy(editSub);

    labelPost = new QLabel(tr("Post:"));
    editPost = new LineEdit;
    editPost->setReadOnly(true);
    labelPost->setBuddy(editPost);

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
    
    //tableView = new QTableView(this);
    //templateModel = new QSqlRelationalTableModel(this);
    //templateModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    QPushButton *addTableButton = new QPushButton(tr("Add"));
    QPixmap pixAdd(":/add.png");
    addTableButton->setIcon(pixAdd);
    //connect(addTableButton,SIGNAL(clicked()),this,SLOT(addRecordOfTable()));

    QPushButton *deleteTableButton = new QPushButton(tr("Delete"));
    QPixmap pixDelete(":/delete.png");
    deleteTableButton->setIcon(pixDelete);
    //connect(deleteRecordButton,SIGNAL(clicked()),this,SLOT(deleteRecordOfTable()));

    QPushButton *editTableButton = new QPushButton(tr("Edit"));
    QPixmap pixEdit(":/edit.png");
    editTableButton->setIcon(pixEdit);
    //connect(editRecordButton,SIGNAL(clicked()),this,SLOT(editRecordOfTable()));

    QHBoxLayout *buttonTableBox = new QHBoxLayout;
    buttonTableBox->addWidget(addTableButton);
    buttonTableBox->addWidget(deleteTableButton);
    buttonTableBox->addWidget(editTableButton);
    buttonTableBox->addStretch();

    //connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editRecordOfTable()));

    //*****************************************************
    //Filter for table
    //*****************************************************
    QString filterID = "treatmentdocid = '";
    filterID += indexTemp;
    filterID += "'";

    //*****************************************************
    //Medical Service
    //*****************************************************
    QTableView *medicalServiceWidget = new QTableView;
    QSqlRelationalTableModel *medicalServiceModel = new QSqlRelationalTableModel;
    medicalServiceModel->setTable("treatmentservice");
    medicalServiceModel->setFilter(filterID);
    medicalServiceModel->setHeaderData(2,Qt::Horizontal,tr("Medical Service"));
    medicalServiceModel->setRelation(2,QSqlRelation("medicalservice","medicalserviceid","medicalservicename"));
    medicalServiceModel->select();
    medicalServiceWidget->setModel(medicalServiceModel);
    medicalServiceWidget->setColumnHidden(0,true);
    medicalServiceWidget->setColumnHidden(1,true);
    medicalServiceWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    medicalServiceWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    medicalServiceWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    medicalServiceWidget->setAlternatingRowColors(true);
    medicalServiceWidget->resizeColumnsToContents();
    //educationWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    QHeaderView *headMedicalService = medicalServiceWidget->horizontalHeader();
    headMedicalService->setStretchLastSection(true);

    QTableView *prepatationWidget = new QTableView;
    QSqlRelationalTableModel *prepatationModel = new QSqlRelationalTableModel;
    prepatationModel->setTable("treatmentpreparation");
    prepatationModel->setFilter(filterID);
    prepatationModel->setHeaderData(2,Qt::Horizontal,tr("Preparation"));
    prepatationModel->setRelation(2,QSqlRelation("preparation","preparationid","preparationname"));
    prepatationModel->select();
    prepatationWidget->setModel(prepatationModel);
    prepatationWidget->setColumnHidden(0,true);
    prepatationWidget->setColumnHidden(1,true);
    prepatationWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    prepatationWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    prepatationWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    prepatationWidget->setAlternatingRowColors(true);
    prepatationWidget->resizeColumnsToContents();
    //educationWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    QHeaderView *headPrepatation = prepatationWidget->horizontalHeader();
    headPrepatation->setStretchLastSection(true);

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->addTab(medicalServiceWidget,tr("Medical Service"));
    tabWidget->addTab(prepatationWidget,tr("Preparation"));

    if(indexTemp != ""){
        QSqlQuery query;
        query.prepare("SELECT (SELECT emp.employeename FROM employee AS emp WHERE emp.employeeid = treat.employeeid), treat.date FROM treatmentdoc AS treat WHERE treat.treatmendoctid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editFIO->setText(query.value(0).toString());
            editDateDoc->setDate(query.value(1).toDate());
        }
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelNumberDoc,0,0);
    mainLayout->addWidget(editNumberDoc,0,1);
    mainLayout->addWidget(labelDateDoc,0,2);
    mainLayout->addWidget(editDateDoc,0,3);
    mainLayout->addWidget(labelFIO,1,0);
    mainLayout->addLayout(empLayout,1,1,1,3);
    mainLayout->addWidget(labelOrg,2,0);
    mainLayout->addWidget(editOrg,2,1,1,3);
    mainLayout->addWidget(labelSub,3,0);
    mainLayout->addWidget(editSub,3,1,1,3);
    mainLayout->addWidget(labelPost,4,0);
    mainLayout->addWidget(editPost,4,1,1,3);
    mainLayout->addLayout(buttonTableBox,5,0,1,4);
    mainLayout->addWidget(tabWidget,6,0,1,4);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,7,3);
        editFIO->selectAll();
    }

    setLayout(mainLayout);

    setWindowTitle(tr("Treatment Doc"));

    exchangeFile.setFileName("exchange.txt");
    if(!exchangeFile.isOpen()){
        exchangeFile.open(QIODevice::ReadWrite);
    }
}

void TreatmentDocForm::deleteRecord()
{
    ForDelete forDelete(indexTemp,"treatmentdoc",this);
    forDelete.result();
    forDelete.deleteOnDefault();
    QTextStream stream(&exchangeFile);
    QString line;
    while(!stream.atEnd()){
        stream.readLine();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM treatmentdoc WHERE treatmentdocid = :id");
    query.bindValue(":id",indexTemp);
    query.exec();
    query.next();
    line += "DELETE FROM treatmentdoc WHERE treatmentdocid = '";
    line += indexTemp;
    line += "'";
    line += "\r\n";
    stream<<line;
}

void TreatmentDocForm::editRecord()
{
    if(!editFIO->text().isEmpty()){
        QTextStream stream(&exchangeFile);
        QString line;
        while(!stream.atEnd()){
            stream.readLine();
        }
        if(indexTemp != ""){
            QSqlQuery query;
            query.prepare("UPDATE treatmentdoc SET employeeid = (SELECT emp.employeeid FROM employee AS emp WHERE emp.employeename = :name), date = :date"
                          " WHERE treatmentdocid = :id");
            query.bindValue(":name",editFIO->text());
            query.bindValue(":id",indexTemp);
            query.bindValue(":date",editDateDoc->date());
            query.exec();
            line += "UPDATE treatmentdoc SET employeeid = (SELECT emp.employeeid FROM employee AS emp WHERE emp.employeename = '";
            line += editFIO->text().toUtf8();
            line += "', date = '";
            line += editDateDoc->date().toString();
            line += "' WHERE treatmentdocid = '";
            line += indexTemp;
            line += "'";
            line += "\r\n";
            stream<<line;
        }else{
            QSqlQuery query;
            query.prepare("SELECT * FROM treatmentdoc WHERE treatmentdocid = :id");
            query.bindValue(":id",indexTemp);
            query.exec();
            query.next();
            if(!query.isValid()){
                NumPrefix numPrefix(this);
                indexTemp = numPrefix.getPrefix("treatmentdoc");
                if(indexTemp == ""){
                    close();
                }else{
                    QSqlQuery query;
                    query.prepare("INSERT INTO treatmentdoc (treatmentdocid, employeeid, date) "
                                  "VALUES(:id, (SELECT employeeid FROM employee WHERE employeename = :name), :date)");
                    query.bindValue(":id",indexTemp);
                    query.bindValue(":name",editFIO->text().simplified());
                    query.bindValue(":date",editDateDoc->date());
                    query.exec();
                    line += "INSERT INTO treatmentdoc (treatmentdocid, employeeid, date) VALUES('";
                    line += indexTemp;
                    line += "', (SELECT employeeid FROM employee WHERE employeename = '";
                    line += editFIO->text().toUtf8();
                    line += "', ";
                    line += editDateDoc->date().toString();
                    line += "')";
                    line += "\r\n";
                    stream<<line;
                }
            }else{
                QString tempString = editNumberDoc->text();
                tempString += QObject::tr(" from ");
                tempString += editDateDoc->date().toString();
                tempString += QObject::tr(" is availble!");
                QMessageBox::warning(this,QObject::tr("Attention!!!"),tempString);
            }
        }
        emit accept();
        close();
    }else{
        QMessageBox::warning(this,QObject::tr("Attention!!!"),tr("FIO don't be empty!"));
    }
}

void TreatmentDocForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void TreatmentDocForm::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("Treatmentdoc").toByteArray());
}

void TreatmentDocForm::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("Treatmentdoc", saveGeometry());
}

void TreatmentDocForm::addEmpRecord()
{

}

void TreatmentDocForm::seeEmpRecord()
{

}

void TreatmentDocForm::listEmpRecord()
{

}

void TreatmentDocForm::fioChange()
{
    qDebug()<<"sql";
    QSqlQuery query;
    query.prepare("SELECT (SELECT org.organizationname FROM organization AS org WHERE org.organizationid = emp.organizationid), "
                  "(SELECT sub.subdivisionname FROM subdivision AS sub WHERE sub.subdivisionid = emp.subdivisionid), "
                  "(SELECT pos.postname FROM post AS pos WHERE pos.postid = emp.postid) FROM employee AS emp WHERE emp.employeename = :name");
    query.bindValue(":name",editFIO->text());
    query.exec();
    query.next();
    editOrg->setText(query.value(0).toString());
    editSub->setText(query.value(1).toString());
    editPost->setText(query.value(2).toString());
}
