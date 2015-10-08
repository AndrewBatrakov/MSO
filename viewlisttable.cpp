#include <QtGui>
#include <QtSql>

#include "viewlisttable.h"
#include "diseaseform.h"
#include "employeeform.h"
#include "locationform.h"
#include "medicalserviceform.h"
#include "nodeform.h"
#include "postform.h"
#include "subdivisionform.h"
#include "treatmentform.h"
#include "typeofworkform.h"
#include "searchform.h"

ViewListTable::ViewListTable(QString idTable, QString nameTable, QWidget *parent) :
    QDialog(parent)
{
    tableName = nameTable;
    iDTemp = idTable;
    labelName = "";

    addButton = new QPushButton(tr("Add record"));
    QPixmap pixAdd(":/add.png");
    addButton->setIcon(pixAdd);
    connect(addButton,SIGNAL(clicked()),this,SLOT(addRecord()));

    deleteButton = new QPushButton(tr("Delete record"));
    QPixmap pixDel(":/delete.png");
    deleteButton->setIcon(pixDel);
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteRecord()));

    editButton = new QPushButton(tr("Edit record"));
    QPixmap pixEdit(":/edit.png");
    editButton->setIcon(pixEdit);
    connect(editButton,SIGNAL(clicked()),this,SLOT(editRecord()));

    searchButton = new QPushButton(tr("Search (by Name)"));
    connect(searchButton,SIGNAL(clicked()),this,SLOT(searchProcedure()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addStretch();

    tableView = new QTableView;
    tableView->clearSpans();

    templateModel = new QSqlRelationalTableModel(this);

    viewTemplateTable(tableName);
    if(iDTemp != ""){
        for(int row = 0; row  < templateModel->rowCount(); ++row){
            QSqlRecord record = templateModel->record(row);
            QModelIndex index = templateModel->index(row,1);
            if(record.value(0).toString() == iDTemp){
                tableView->setCurrentIndex(index);
                break;
            }
        }
    }else{
        tableView->setCurrentIndex(templateModel->index(0,0));
    }

    tableView->resizeColumnsToContents();
    tableView->setAlternatingRowColors(true);
    QHeaderView *header = tableView->horizontalHeader();
    header->setStretchLastSection(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableView);
    setLayout(mainLayout);

    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(accept()));

    setWindowTitle(tr("List of %1").arg(labelName));
    resize(tableView->size().width()+200,tableView->size().height());

    createContextMenu();
}

void ViewListTable::viewTemplateTable(QString)
{
    templateModel->setTable(tableName);

    if(tableName == "disease"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        labelName = "Diseases";
        if(setFilter){
            templateModel->setFilter(QString("diseasename LIKE '%%1%'").arg(filterTable));
        }
    }else if(tableName == "subdivision"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        labelName = "Subdivisions";
        if(setFilter){
            templateModel->setFilter(QString("subdivisionname LIKE '%%1%'").arg(filterTable));
        }
    }if(tableName == "location"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        labelName = "Locations";
        if(setFilter){
            templateModel->setFilter(QString("locationname LIKE '%%1%'").arg(filterTable));
        }
    }else if(tableName == "medicalservice"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        templateModel->setHeaderData(2,Qt::Horizontal,tr("Cost"));
        labelName = "Medical Services";
        if(setFilter){
            templateModel->setFilter(QString("medicalservicename LIKE '%%1%'").arg(filterTable));
        }
    }else if(tableName == "node"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Code"));
        templateModel->setHeaderData(2,Qt::Horizontal,tr("Name"));
        templateModel->setHeaderData(3,Qt::Horizontal,tr("Head"));
        labelName = "Nodes";
        if(setFilter){
            templateModel->setFilter(QString("nodename LIKE '%%1%'").arg(filterTable));
        }
    }else if(tableName == "post"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        labelName = "Posts";
        if(setFilter){
            templateModel->setFilter(QString("postname LIKE '%%1%'").arg(filterTable));
        }
    }else if(tableName == "employee"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("FIO"));
        templateModel->setRelation(2,QSqlRelation("subdivision","subdivisionid","subdivisionname"));
        templateModel->setRelation(3,QSqlRelation("post","postid","postname"));
        labelName = "Employees";
        if(setFilter){
            templateModel->setFilter(QString("employeename LIKE '%%1%'").arg(filterTable));
        }
    }else if(tableName == "treatment"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        labelName = "Treatments";
        if(setFilter){
            templateModel->setFilter(QString("treatmentname LIKE '%%1%'").arg(filterTable));
        }
    }else if(tableName == "typeofwork"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        labelName = "Type Of Work";
        if(setFilter){
            templateModel->setFilter(QString("typeofworkname LIKE '%%1%'").arg(filterTable));
        }
    }

    templateModel->setSort(1,Qt::AscendingOrder);
    templateModel->select();
    tableView->setModel(templateModel);
    tableView->setColumnHidden(0,true);
//    if(tableName == "employee"){
//        tableView->setColumnHidden(2,true);
//        tableView->setColumnHidden(5,true);
//        for(int i = 7; i < 15; ++i){
//            tableView->setColumnHidden(i,true);
//        }
//    }else if(tableName == "empcertdate"){
//        //tableView->setColumnHidden(1,true);
//    }
    tableView->setItemDelegate(new QSqlRelationalDelegate(this));
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ViewListTable::done(int res)
{
    if(res == QDialog::Accepted){
        QModelIndex index = tableView->currentIndex();
        if(index.isValid()){
            QSqlRecord record = templateModel->record(index.row());
            QString per = tableName;
            per += "id";
            iDTemp = record.value(per).toString();
        }else{
            iDTemp = "";
        }
    }
    QDialog::done(res);
}

void ViewListTable::addRecord()
{
    QString nameList;
    if(tableName == "disease"){
        DiseaseForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "subdivision"){
        SubdivisionForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "employee"){
        EmployeeForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "location"){
        LocationForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "medicalservice"){
        MedicalServiceForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "node"){
        NodeForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "post"){
        PostForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "treatment"){
        TreatmentForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }else if(tableName == "typeofwork"){
        TypeOfWorkForm listForm("",this,false);
        listForm.exec();
        nameList = listForm.rowOut();
    }
    templateModel->select();
    for(int row = 0; row < templateModel->rowCount(); ++row){
        QSqlRecord record = templateModel->record(row);
        QModelIndex index = templateModel->index(row,1);
        if(record.value(0).toString() == nameList){
            tableView->setCurrentIndex(index);
            updatePanel(index);
            break;
        }
    }
}

void ViewListTable::deleteRecord()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Attention!!!"));
    msgBox.setText(tr("Really delete?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(QMessageBox::Yes);
    QPushButton *noButton = msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(noButton);

    noButton->setStyleSheet("QPushButton:hover {color: red}");
    int k = msgBox.exec();
    if(k == QMessageBox::Yes){
        QModelIndex index = tableView->currentIndex();
        QSqlRecord record = templateModel->record(index.row());
        QString idList = record.value(0).toString();
        if(tableName == "post"){
            PostForm listForm(idList,this,false);
            listForm.deleteRecord();
        }else if(tableName == "subdivision"){
            SubdivisionForm listForm(idList,this,false);
            listForm.deleteRecord();
//        }else if(tableName == "legalacts"){
//            LegalAct listForm(idList,this,false);
//            listForm.deleteRecord();
//        }else if(tableName == "safetyreq"){
//            SafetyRequirements listForm(idList,this,false);
//            listForm.deleteRecord();
//        }else if(tableName == "testtask"){
//            TestTask listForm(idList,this,false);
//            listForm.deleteRecord();
        }
        updatePanel(index);
    }
}

void ViewListTable::editRecord()
{
    QModelIndex index = tableView->currentIndex();
    QSqlRecord record = templateModel->record(index.row());
    QString idList = record.value(0).toString();
    if(tableName == "post"){
        PostForm listFrom(idList,this,false);
        listFrom.exec();
    }else if(tableName == "subdivision"){
        SubdivisionForm listFrom(idList,this,false);
        listFrom.exec();
//    }else if(tableName == "legalacts"){
//        LegalAct listFrom(idList,this,false);
//        listFrom.exec();
//    }else if(tableName == "safetyreq"){
//        SafetyRequirements listFrom(idList,this,false);
//        listFrom.exec();
//    }else if(tableName == "testtask"){
//        TestTask listFrom(idList,this,false);
//        listFrom.exec();
//    }else if(tableName == "empcertdate"){
//        EmpCertDate listFrom(idList,this,false);
//        listFrom.exec();
    }
    updatePanel(index);
}

void ViewListTable::updatePanel(QModelIndex index)
{
    templateModel->select();
    tableView->setCurrentIndex(index);
}

void ViewListTable::createContextMenu()
{
    addAction = new QAction(tr("Add Record"),this);
    QPixmap pixAdd(":/add.png");
    addAction->setIcon(pixAdd);
    connect(addAction,SIGNAL(triggered()),this,SLOT(addRecord()));

    QPixmap pixDelete(":/delete.png");
    deleteAction = new QAction(tr("Delete Record"),this);
    deleteAction->setIcon(pixDelete);
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteRecord()));

    QPixmap pixEdit(":/edit.png");
    editAction = new QAction(tr("Edit Record"),this);
    editAction->setIcon(pixEdit);
    connect(editAction,SIGNAL(triggered()),this,SLOT(editRecord()));

    tableView->addAction(addAction);
    tableView->addAction(deleteAction);
    tableView->addAction(editAction);
    tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void ViewListTable::searchProcedure()
{
    QString valueTempModel = templateModel->tableName();

    SearchForm searchForm(valueTempModel, this);
    searchForm.exec();
    filterTable = searchForm.rowOut();
    setFilter = true;

    viewTemplateTable(valueTempModel);
}
