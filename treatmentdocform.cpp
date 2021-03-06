#include "treatmentdocform.h"
#include <QtSql>
#include "fordelete.h"
#include "numprefix.h"
#include "employeeform.h"
#include "viewlisttable.h"
#include "medicalserviceform.h"
#include "preparationform.h"

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

    labelItogoService = new QLabel(tr("Itogo Medical Service:"));
    //labelItogoService->setStyleSheet("QLabel {font: Bold; font-size: 16px}");
    editItogoService = new QLabel;
    editItogoService->setStyleSheet("QLabel {font: Bold, font-size: 14px}");

    labelItogoPreparation = new QLabel(tr("Itogo Preparation:"));
    //labelItogoPreparation->setStyleSheet("QLabel {font: Bold}");
    editItogoPreparation = new QLabel;
    editItogoPreparation->setStyleSheet("QLabel {font: Bold, font-size: 14px}");

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
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveRecord()));
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
    connect(addTableButton,SIGNAL(clicked()),this,SLOT(addRecordOfTable()));

    QPushButton *deleteTableButton = new QPushButton(tr("Delete"));
    QPixmap pixDelete(":/delete.png");
    deleteTableButton->setIcon(pixDelete);
    connect(deleteTableButton,SIGNAL(clicked()),this,SLOT(deleteRecordOfTable()));

    QPushButton *editTableButton = new QPushButton(tr("Edit"));
    QPixmap pixEdit(":/edit.png");
    editTableButton->setIcon(pixEdit);
    connect(editTableButton,SIGNAL(clicked()),this,SLOT(editRecordOfTable()));

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
    medicalServiceWidget = new QTableWidget(0,6);
    medicalServiceWidget->setHorizontalHeaderLabels(QStringList()<<tr("Name")<<tr("Time")<<tr("Cost")<<tr("Summa"));
    QHeaderView *headMS = medicalServiceWidget->horizontalHeader();
    medicalServiceWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    medicalServiceWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //medicalServiceWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    medicalServiceWidget->setAlternatingRowColors(true);
    medicalServiceWidget->resizeColumnsToContents();
    //tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    headMS->setStretchLastSection(true);

    preparationWidget = new QTableWidget(0,6);
    preparationWidget->setHorizontalHeaderLabels(QStringList()<<tr("Name")<<tr("Number")<<tr("Cost")<<("Summa"));
    QHeaderView *headP = preparationWidget->horizontalHeader();
    preparationWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    preparationWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //preparationWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    preparationWidget->setAlternatingRowColors(true);
    preparationWidget->resizeColumnsToContents();
    //tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    headP->setStretchLastSection(true);

    tabWidget = new QTabWidget;
    tabWidget->addTab(medicalServiceWidget,tr("Medical Service"));
    tabWidget->addTab(preparationWidget,tr("Preparation"));

    //запрещаем редактирование столбца
    medicalServiceWidget->setItemDelegateForColumn(0, new NonEditTableColumnDelegate());
    medicalServiceWidget->setColumnWidth(0,200);
    medicalServiceWidget->setItemDelegateForColumn(2, new NonEditTableColumnDelegate());
    medicalServiceWidget->setColumnWidth(2,75);
    medicalServiceWidget->setItemDelegateForColumn(3, new NonEditTableColumnDelegate());
    medicalServiceWidget->setColumnHidden(4,true);
    medicalServiceWidget->setColumnHidden(5,true);
    connect(medicalServiceWidget,SIGNAL(cellChanged(int,int)),this,SLOT(changeItemService(int,int)));
    //    connect(medicalServiceWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(editRecordOfTable()));
    //    connect(preparationWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(editRecordOfTable()));

    //запрещаем редактирование столбца
    preparationWidget->setItemDelegateForColumn(0, new NonEditTableColumnDelegate());
    preparationWidget->setColumnWidth(0,200);
    preparationWidget->setItemDelegateForColumn(2, new NonEditTableColumnDelegate());
    preparationWidget->setColumnWidth(2,75);
    preparationWidget->setItemDelegateForColumn(3, new NonEditTableColumnDelegate());
    preparationWidget->setColumnHidden(4,true);
    preparationWidget->setColumnHidden(5,true);
    connect(preparationWidget,SIGNAL(cellChanged(int,int)),this,SLOT(changeItemPreparation(int,int)));

    if(indexTemp != ""){
        QSqlQuery query;
        query.prepare("SELECT (SELECT emp.employeename FROM employee AS emp WHERE emp.employeeid = tr.employeeid), tr.treatmentdocdate FROM treatmentdoc AS tr WHERE tr.treatmentdocid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        while(query.next()){
            editFIO->setText(query.value(0).toString());
            editDateDoc->setDate(query.value(1).toDate());
            editNumberDoc->setText(indexTemp);
            int row = 0;
            QSqlQuery queryDoc;
            queryDoc.prepare("SELECT medicalserviceid, number, treatmentserviceid FROM treatmentservice WHERE treatmentdocid = :id");
            queryDoc.bindValue(":id",indexTemp);
            queryDoc.exec();
            while(queryDoc.next()){
            QSqlQuery queryMedicalService;
            queryMedicalService.prepare("SELECT * FROM medicalservice WHERE medicalserviceid = :mdid");
            queryMedicalService.bindValue(":mdid",queryDoc.value(0).toString());
            queryMedicalService.exec();
            while(queryMedicalService.next()){
                medicalServiceWidget->insertRow(row);
                QTableWidgetItem *item = new QTableWidgetItem;
                medicalServiceWidget->setItem(row,0,item);
                medicalServiceWidget->item(row,0)->setText(queryMedicalService.value(1).toString());

                QTableWidgetItem *item2 = new QTableWidgetItem;
                medicalServiceWidget->setItem(row,2,item2);
                double column2 = queryMedicalService.value(2).toDouble();
                medicalServiceWidget->item(row,2)->setText(QString::number(column2,'f',2));
                QTableWidgetItem *item3 = new QTableWidgetItem;
                medicalServiceWidget->setItem(row,3,item3);
                medicalServiceWidget->item(row,3)->setText("0");
                QTableWidgetItem *item5 = new QTableWidgetItem;
                medicalServiceWidget->setItem(row,5,item5);
                medicalServiceWidget->item(row,5)->setText(queryDoc.value(2).toString());
                QTableWidgetItem *item4 = new QTableWidgetItem;
                medicalServiceWidget->setItem(row,4,item4);
                medicalServiceWidget->item(row,4)->setText(queryMedicalService.value(0).toString());
                QTableWidgetItem *item1 = new QTableWidgetItem;
                medicalServiceWidget->setItem(row,1,item1);
                double column1 = queryDoc.value(1).toDouble();
                medicalServiceWidget->item(row,1)->setText(QString::number(column1,'f',2));
                ++row;
            }
            }
            row = 0;
            QSqlQuery queryDoc1;
            queryDoc1.prepare("SELECT preparationid, number, treatmentpreparationid FROM treatmentpreparation WHERE treatmentdocid = :id");
            queryDoc1.bindValue(":id",indexTemp);
            queryDoc1.exec();
            queryDoc1.next();
            QSqlQuery queryPreparation;
            queryPreparation.prepare("SELECT * FROM preparation WHERE preparationid = :prid");
            queryPreparation.bindValue(":prid",queryDoc1.value(0).toString());
            queryPreparation.exec();
            while(queryPreparation.next()){
                preparationWidget->insertRow(row);
                QTableWidgetItem *item = new QTableWidgetItem;
                preparationWidget->setItem(row,0,item);
                preparationWidget->item(row,0)->setText(queryPreparation.value(1).toString());
                QTableWidgetItem *item2 = new QTableWidgetItem;
                preparationWidget->setItem(row,2,item2);
                double column2 = queryPreparation.value(2).toDouble();
                preparationWidget->item(row,2)->setText(QString::number(column2,'f',2));
                QTableWidgetItem *item3 = new QTableWidgetItem;
                preparationWidget->setItem(row,3,item3);
                preparationWidget->item(row,3)->setText("0");
                QTableWidgetItem *item5 = new QTableWidgetItem;
                preparationWidget->setItem(row,5,item5);
                preparationWidget->item(row,5)->setText(queryDoc1.value(2).toString());
                QTableWidgetItem *item4 = new QTableWidgetItem;
                preparationWidget->setItem(row,4,item4);
                preparationWidget->item(row,4)->setText(queryPreparation.value(0).toString());
                QTableWidgetItem *item1 = new QTableWidgetItem;
                preparationWidget->setItem(row,1,item1);
                double column1 = queryDoc1.value(1).toDouble();
                preparationWidget->item(row,1)->setText(QString::number(column1,'f',2));
                ++row;
            }
        }
    }else{
        NumPrefix numPrefix(this);
        indexTemp = numPrefix.getPrefix("treatmentdoc");
        if(indexTemp == ""){
            close();
        }
        editNumberDoc->setText(indexTemp);
    }

    QGridLayout *itogoLayout = new QGridLayout;
    itogoLayout->addWidget(labelItogoService,0,0);
    itogoLayout->addWidget(editItogoService,0,1);
    itogoLayout->addWidget(labelItogoPreparation,1,0);
    itogoLayout->addWidget(editItogoPreparation,1,1);

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
    mainLayout->addLayout(itogoLayout,7,3);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,8,3);
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

        QSqlQuery query;
        query.prepare("SELECT * FROM treatmentdoc WHERE treatmentdocid = :id");
        query.bindValue(":id",indexTemp);
        query.exec();
        query.next();
        if(query.isValid()){
            QSqlQuery query;
            query.prepare("UPDATE treatmentdoc SET employeeid = (SELECT emp.employeeid FROM employee AS emp WHERE emp.employeename = :name), treatmentdocdate = :date"
                          " WHERE treatmentdocid = :id");
            query.bindValue(":name",editFIO->text());
            query.bindValue(":id",indexTemp);
            query.bindValue(":date",editDateDoc->date());
            query.exec();

            line += "UPDATE treatmentdoc SET employeeid = (SELECT emp.employeeid FROM employee AS emp WHERE emp.employeename = '";
            line += editFIO->text().toUtf8();
            line += "', treatmentdocdate = '";
            line += editDateDoc->date().toString();
            line += "' WHERE treatmentdocid = '";
            line += indexTemp;
            line += "'";
            line += "\r\n";
            stream<<line;
        }else{
            QSqlQuery query;
            query.prepare("INSERT INTO treatmentdoc (treatmentdocid, employeeid, treatmentdocdate) "
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

void TreatmentDocForm::saveRecord()
{
    for(int i = 0; i < medicalServiceWidget->rowCount(); ++i){
        if(medicalServiceWidget->item(i,1)->text() == "0"){
            QString tt = medicalServiceWidget->item(i,0)->text();
            tt += tr(", Time must be > 0!");
            QMessageBox::warning(this,QObject::tr("Attention!!!"),tt);
            return;
        }
    }
    for(int i = 0; i < preparationWidget->rowCount(); ++i){
        if(preparationWidget->item(i,1)->text() == "0"){
            QString tt = preparationWidget->item(i,0)->text();
            tt += tr(", Number must be > 0!");
            QMessageBox::warning(this,QObject::tr("Attention!!!"),tt);
            return;
        }
    }
    editRecord();
    emit accept();
}

void TreatmentDocForm::addEmpRecord()
{
    EmployeeForm openForm("",this,false);
    openForm.exec();
    if(openForm.rowOut() != ""){
        QSqlQuery query;
        query.prepare("SELECT employeename FROM employee WHERE employeeid = :id");
        query.bindValue(":id",openForm.rowOut());
        query.exec();
        query.next();
        editFIO->setText(query.value(0).toString());
    }
}

void TreatmentDocForm::seeEmpRecord()
{
    QSqlQuery query;
    query.prepare("SELECT employeeid FROM employee WHERE employeename = :name");
    query.bindValue(":name",editFIO->text());
    query.exec();
    while(query.next()){
        EmployeeForm openForm(query.value(0).toString(),this,true);
        openForm.exec();
    }
}

void TreatmentDocForm::listEmpRecord()
{
    QSqlQuery query;
    query.prepare("SELECT employeeid FROM employee WHERE employeename = :name");
    query.bindValue(":name",editFIO->text());
    query.exec();
    query.next();
    ViewListTable listTemp(query.value(0).toString(),"employee",this);
    listTemp.exec();
    if(listTemp.rowOut() != ""){
        QSqlQuery query;
        query.prepare("SELECT employeename FROM employee WHERE employeeid = :id");
        query.bindValue(":id",listTemp.rowOut());
        query.exec();
        query.next();
        editFIO->setText(query.value(0).toString());
    }
}

void TreatmentDocForm::fioChange()
{
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

void TreatmentDocForm::addRecordOfTable()
{
    if(!editFIO->text().isEmpty()){

        int row = medicalServiceWidget->rowCount();

        if(medicalServiceWidget->isVisible()){
            ViewListTable listTemp("","medicalservice",this);
            listTemp.exec();
            QString idMS = listTemp.rowOut();
            QString nameMS;
            if(idMS != ""){
                bool noRecord = true;
                for(int i = 0; i < medicalServiceWidget->rowCount(); ++i){
                    if(medicalServiceWidget->item(i,4)->text() == idMS){
                        noRecord = false;
                        nameMS = medicalServiceWidget->item(i,0)->text();
                    }
                }
                if(noRecord){
                    QSqlQuery query;
                    query.prepare("SELECT medicalservicename, cost, medicalserviceid FROM medicalservice WHERE medicalserviceid = :id");
                    query.bindValue(":id",idMS);
                    query.exec();
                    query.next();

                    medicalServiceWidget->insertRow(row);
                    QTableWidgetItem *item = new QTableWidgetItem;
                    medicalServiceWidget->setItem(row,0,item);
                    medicalServiceWidget->item(row,0)->setText(query.value(0).toString());
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    medicalServiceWidget->setItem(row,2,item2);
                    double column2 = query.value(1).toDouble();
                    medicalServiceWidget->item(row,2)->setText(QString::number(column2,'f',2));
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    medicalServiceWidget->setItem(row,3,item3);
                    medicalServiceWidget->item(row,3)->setText("0");
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    medicalServiceWidget->setItem(row,1,item1);
                    medicalServiceWidget->item(row,1)->setText("0");

                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    medicalServiceWidget->setItem(row,4,item4);
                    medicalServiceWidget->item(row,4)->setText(query.value(2).toString());

                    NumPrefix numPrefix(this);
                    QString indexMS = numPrefix.getPrefix("treatmentservice");
                    if(indexMS == ""){
                        close();
                    }

                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    medicalServiceWidget->setItem(row,5,item5);
                    medicalServiceWidget->item(row,5)->setText(indexMS);

                    QSqlQuery queryMS;
                    queryMS.prepare("INSERT INTO treatmentservice (treatmentserviceid, treatmentdocid, medicalserviceid, number) "
                                    "VALUES(:treatmentserviceid, :treatmentdocid, :medicalserviceid, :time)");
                    queryMS.bindValue(":treatmentserviceid",indexMS);
                    queryMS.bindValue(":treatmentdocid",indexTemp);
                    queryMS.bindValue(":medicalserviceid",medicalServiceWidget->item(row,4)->text());
                    queryMS.bindValue(":time",medicalServiceWidget->item(row,1)->text());
                    queryMS.exec();
                }else{
                    QString tempString = nameMS;
                    tempString += QObject::tr(" is availble!");
                    QMessageBox::warning(this,QObject::tr("Attention!!!"),tempString);
                }
            }

        }

        row = preparationWidget->rowCount();
        if(preparationWidget->isVisible()){
            ViewListTable listTemp("","preparation",this);
            listTemp.exec();
            QString idMS = listTemp.rowOut();
            QString nameMS;
            if(idMS != ""){
                bool noRecord = true;
                for(int i = 0; i < preparationWidget->rowCount(); ++i){
                    if(preparationWidget->item(i,4)->text() == idMS){
                        noRecord = false;
                        nameMS = preparationWidget->item(i,0)->text();
                    }
                }
                if(noRecord){
                    QSqlQuery query;
                    query.prepare("SELECT preparationname, cost, preparationid FROM preparation WHERE preparationid = :id");
                    query.bindValue(":id",idMS);
                    query.exec();
                    query.next();
                    preparationWidget->insertRow(row);
                    QTableWidgetItem *item = new QTableWidgetItem;
                    preparationWidget->setItem(row,0,item);
                    preparationWidget->item(row,0)->setText(query.value(0).toString());
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    preparationWidget->setItem(row,2,item2);
                    double column2 = query.value(1).toDouble();
                    preparationWidget->item(row,2)->setText(QString::number(column2,'f',2));
                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    preparationWidget->setItem(row,4,item4);
                    preparationWidget->item(row,4)->setText(query.value(2).toString());
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    preparationWidget->setItem(row,3,item3);
                    preparationWidget->item(row,3)->setText("0");
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    preparationWidget->setItem(row,1,item1);
                    preparationWidget->item(row,1)->setText("0");

                    NumPrefix numPrefix(this);
                    QString indexP = numPrefix.getPrefix("treatmentpreparation");
                    if(indexP == ""){
                        close();
                    }

                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    preparationWidget->setItem(row,5,item5);
                    preparationWidget->item(row,5)->setText(indexP);

                    QSqlQuery queryP;
                    queryP.prepare("INSERT INTO treatmentpreparation (treatmentpreparationid, treatmentdocid, preparationid, number) "
                                    "VALUES(:treatmentpreparationid, :treatmentdocid, :preparationid, :time)");
                    queryP.bindValue(":treatmentpreparationid",indexP);
                    queryP.bindValue(":treatmentdocid",indexTemp);
                    queryP.bindValue(":preparationid",medicalServiceWidget->item(row,4)->text());
                    queryP.bindValue(":time",medicalServiceWidget->item(row,1)->text());
                    queryP.exec();
                }else{
                    QString tempString = nameMS;
                    tempString += QObject::tr(" is availble!");
                    QMessageBox::warning(this,QObject::tr("Attention!!!"),tempString);
                }
            }
        }
    }else{
        QMessageBox::warning(this,QObject::tr("Attention!!!"),tr("FIO don't be empty!"));
    }
}

void TreatmentDocForm::deleteRecordOfTable()
{
    int k = QMessageBox::question(this,tr("Attention!!"),
                                  tr("Really delete?"),
                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(k == QMessageBox::Yes){

        if(medicalServiceWidget->isVisible()){
            QSqlQuery queryMS;
            queryMS.prepare("DELETE FROM treatmentservice WHERE treatmentserviceid = :id;");
            queryMS.bindValue(":id",medicalServiceWidget->item(medicalServiceWidget->currentRow(),4)->text());
            queryMS.exec();
            medicalServiceWidget->removeRow(medicalServiceWidget->currentRow());
            medicalServiceWidget->repaint();
        }

        if(preparationWidget->isVisible()){
            preparationWidget->removeRow(preparationWidget->currentRow());
            preparationWidget->repaint();
        }
    }
}


void TreatmentDocForm::editRecordOfTable()
{

}

void TreatmentDocForm::changeItemService(int row, int column)
{
    if(column == 1){
        double column1 = medicalServiceWidget->item(row,1)->text().toDouble();
        double column2 = medicalServiceWidget->item(row,2)->text().toDouble();

        medicalServiceWidget->item(row,3)->setText(QString::number(column1 * column2,'f',2));
        double itog = 0;
        for(int i = 0;i < medicalServiceWidget->rowCount(); ++i){
            itog = itog + medicalServiceWidget->item(i,3)->text().toDouble();
        }
        editItogoService->setText(QString::number(itog,'f',2));
        if(column1 > 0){
            QSqlQuery queryMSU;
            queryMSU.prepare("UPDATE treatmentservice SET number = :number "
                             "WHERE treatmentserviceid = :treatmentserviceid AND treatmentdocid = :treatmentdocid");
            queryMSU.bindValue(":treatmentserviceid",medicalServiceWidget->item(row,5)->text());
            queryMSU.bindValue(":treatmentdocid",indexTemp);
            queryMSU.bindValue(":number",medicalServiceWidget->item(row,1)->text());
            queryMSU.exec();
        }
    }
}

void TreatmentDocForm::changeItemPreparation(int row, int column)
{
    if(column == 1){
        double column1 = preparationWidget->item(row,1)->text().toDouble();
        double column2 = preparationWidget->item(row,2)->text().toDouble();

        preparationWidget->item(row,3)->setText(QString::number(column1 * column2,'f',2));
        double itog = 0;
        for(int i = 0;i < preparationWidget->rowCount(); ++i){
            itog = itog + preparationWidget->item(i,3)->text().toDouble();

        }
        editItogoPreparation->setText(QString::number(itog,'f',2));
        if(column1 > 0){
            QSqlQuery queryP;
            queryP.prepare("UPDATE treatmentpreparation SET number = :number "
                             "WHERE treatmentpreparationid = :treatmentpreparationid AND treatmentdocid = :treatmentdocid");
            queryP.bindValue(":treatmentpreparationid",preparationWidget->item(row,5)->text());
            queryP.bindValue(":treatmentdocid",indexTemp);
            queryP.bindValue(":number",preparationWidget->item(row,1)->text());
            queryP.exec();
        }
    }
}
