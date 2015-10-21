#include "mainwindow.h"
#include <QtSql>
#include "nodeform.h"
#include "boolitemdelegate.h"
#include "exchangeform.h"
#include "prefixnumber.h"
#include "mymodel.h"
#include "smtpform.h"
#include "postform.h"
#include "subdivisionform.h"
#include "putbase.h"
#include "getbase.h"
#include "typeofworkform.h"
#include "locationform.h"
#include "diseaseform.h"
#include "treatmentform.h"
#include "medicalserviceform.h"
#include "employeeform.h"
#include "searchform.h"
#include "organizationform.h"
#include "preparationform.h"
#include "treatmentdocform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    fileExchange.setFileName("exchange.txt");
    fileExchange.open(QIODevice::ReadWrite);
    QPixmap pixLogo(":/logo.png");
    setWindowIcon(pixLogo);
    QString programmName = tr("MSO v.");
    QSettings iniSettings("MSO.ini",QSettings::IniFormat);
    QString version = iniSettings.value("Version").toString();
    programmName += version;
    setWindowTitle(programmName);

#ifdef Q_OS_WIN
    QWidget::setStyleSheet("MainWindow, QMessageBox, QDialog, QMenu, QAction, QMenuBar {background-color: "
                           "#DDD6FF}"
                           "QMenu {"
                           "font: bold}"
                           "QMenu::item:selected {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00}"

                           "QMenuBar::item:selected {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00}"

                           "QPushButton {"
                           "border: 1px solid black;"
                           "min-height: 20px;"
                           "min-width: 70px;"
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

                           "QPushButton:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00}"

                           "QPushButton:focus {border-color: yellow}"
                           "LineEdit:hover {background-color: #FFFF99}"
                           "QComboBox:hover {background-color: #FFFF99}"
                           "QDateEdit:hover {background-color: #FFFF99}"
                           "LineEdit:focus {background-color: #FFFFCC}"
                           "QComboBox:focus {background-color: #FFFFCC}"
                           "QDateEdit:focus {background-color: #FFFFCC}"

                           "QProgressBar {"
                           "border: 1px solid black;"
                           "text-align: center;"
                           "color: #00B600;"
                           "font: bold;"
                           "padding: 1px;"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "border-bottom-right-radius: 5px;"
                           "border-bottom-left-radius: 5px;"
                           "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
                           "stop: 0 #fff,"
                           "stop: 0.4999 #eee,"
                           "stop: 0.5 #ddd,"
                           "stop: 1 #eee );"
                           "width: 15px;"
                           "}"

                           "QProgressBar::chunk {"
                           "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
                           "stop: 0 #78d,"
                           "stop: 0.4999 #46a,"
                           "stop: 0.5 #45a,"
                           "stop: 1 #238 );"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "border-bottom-right-radius: 5px;"
                           "border-bottom-left-radius: 5px;"
                           "border: 1px solid black;}"

                           "QTabWidget::pane {"
                           "border: 1px solid #A3A3FF;"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "border-bottom-right-radius: 5px;"
                           "border-bottom-left-radius: 5px;}"


                           "QTabWidget::tab-bar {"
                           "left: 5px;}"

                           "QTabBar::tab {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #DDD6FF,"
                           "stop:0.5 #A3A3FF,"
                           "stop:0.51 #A3A3FF,"
                           "stop:1 #DDD6FF);"
                           "border: 1px solid #A3A3FF;"
                           "padding: 1px;"
                           "min-width: 90px;"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "font: bold;}"

                           "QTabBar::tab:!selected {background-color: "
                           "#DDD6FF;"
                           "margin-top: 2px;"
                           "font: normal;}"

                           "QTabBar::tab:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;"
                           "font: bold;}"



                           "QSpinBox {padding-left: 15px; padding-right: 15px; border: 1px;}"

                           "QSpinBox::up-button {subcontrol-position: right; subcontrol-origin: border; "
                           "min-width: 15px; min-height: 15px;"
                           "background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #d3d3d3,"
                           "stop:0.5 #bebebe,"
                           "stop:0.51 #bebebe,"
                           "stop:1 #848484);"
                           "color: #231A4C;"
                           "font: bold;}"

                           "QSpinBox::up-button:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;}"

                           "QSpinBox::up-arrow {width: 10px; height: 10px;}"
                           "QSpinBox::down-arrow {width: 10px; height: 10px;}"

                           "QSpinBox::up-arrow {image: url(:/upblack.png);}"

                           "QSpinBox::up-arrow:hover {image: url(:/upgreen.png);}"

                           "QSpinBox::down-arrow {image: url(:/downblack.png);}"

                           "QSpinBox::down-arrow:hover {image: url(:/downred.png);}"

                           "QSpinBox::down-button {subcontrol-position: left; subcontrol-origin: border;"
                           "min-width: 15px; min-height: 15px;"
                           "background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #d3d3d3,"
                           "stop:0.5 #bebebe,"
                           "stop:0.51 #bebebe,"
                           "stop:1 #848484);"
                           "color: #231A4C;"
                           "font: bold;}"

                           "QSpinBox::down-button:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;}"
                           );
#endif
    readSettings();
    createPanel();
    setFilter =false;
    createActions();
    createMenu();
    createContextMenu();
    viewNode();

    /*"top: -0.5em}"
     *
     * "QDoubleSpinBox {padding-left: 15px; padding-right: 15px; border: 1px;}"

    "QDoubleSpinBox::up-button {subcontrol-position: right; subcontrol-origin: border; "
    "min-width: 15px; min-height: 15px;"
    "background-color: "
    "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #d3d3d3,"
    "stop:0.5 #bebebe,"
    "stop:0.51 #bebebe,"
    "stop:1 #848484);"
    "color: #231A4C;"
    "font: bold;}"

    "QDoubleSpinBox::up-button:hover {background-color: "
    "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #cfcccc,"
    "stop:0.5 #333232,"
    "stop:0.51 #000000,"
    "stop:1 #585c5f);"
    "color: #00cc00;}"

    "QDoubleSpinBox::up-arrow {width: 10px; height: 10px;}"
    "QDoubleSpinBox::down-arrow {width: 10px; height: 10px;}"

    "QDoubleSpinBox::up-arrow {image: url(:/upblack.png);}"

    "QDoubleSpinBox::up-arrow:hover {image: url(:/upgreen.png);}"

    "QDoubleSpinBox::down-arrow {image: url(:/downblack.png);}"

    "QDoubleSpinBox::down-arrow:hover {image: url(:/downred.png);}"

    "QDoubleSpinBox::down-button {subcontrol-position: left; subcontrol-origin: border;"
    "min-width: 15px; min-height: 15px;"
    "background-color: "
    "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #d3d3d3,"
    "stop:0.5 #bebebe,"
    "stop:0.51 #bebebe,"
    "stop:1 #848484);"
    "color: #231A4C;"
    "font: bold;}"

    "QDoubleSpinBox::down-button:hover {background-color: "
    "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #cfcccc,"
    "stop:0.5 #333232,"
    "stop:0.51 #000000,"
    "stop:1 #585c5f);"
    "color: #00cc00;}"*/
}

void MainWindow::createPanel()
{
    panel = new QWidget;
    tableLabel = new QLabel;
    tableView = new QTableView(this);
    templateModel = new QSqlRelationalTableModel(this);
    templateModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    addRecordButton = new QPushButton(tr("Add"));
    QPixmap pixAdd(":/add.png");
    addRecordButton->setIcon(pixAdd);
    connect(addRecordButton,SIGNAL(clicked()),this,SLOT(addRecordOfTable()));

    deleteRecordButton = new QPushButton(tr("Delete"));
    QPixmap pixDelete(":/delete.png");
    deleteRecordButton->setIcon(pixDelete);
    connect(deleteRecordButton,SIGNAL(clicked()),this,SLOT(deleteRecordOfTable()));

    editRecordButton = new QPushButton(tr("Edit"));
    QPixmap pixEdit(":/edit.png");
    editRecordButton->setIcon(pixEdit);
    connect(editRecordButton,SIGNAL(clicked()),this,SLOT(editRecordOfTable()));

    QHBoxLayout *buttonBox = new QHBoxLayout;

    buttonBox->addWidget(addRecordButton);
    buttonBox->addWidget(deleteRecordButton);
    buttonBox->addWidget(editRecordButton);
    buttonBox->addStretch();

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonBox);
    mainLayout->addWidget(tableLabel);
    mainLayout->addWidget(tableView);
    panel->setLayout(mainLayout);
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editRecordOfTable()));

    splitterCreate();
}
void MainWindow::readSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    restoreGeometry(settings.value("Geometry").toByteArray());
}

void MainWindow::writeSettings()
{
    QSettings settings("AO_Batrakov_Inc.", "MSO");
    settings.setValue("Geometry", saveGeometry());
    settings.remove("CurrentUser");
}

void MainWindow::createActions()
{
    //File Action
    prefixAction = new QAction(tr("Prefix..."),this);
    connect(prefixAction,SIGNAL(triggered()),this,SLOT(prefixForm()));
    exitAction = new QAction(tr("Exit..."),this);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    //References Action
    organizationAction = new QAction(tr("Organization..."),this);
    connect(organizationAction,SIGNAL(triggered()),this,SLOT(viewOrganization()));
    nodeAction = new QAction(tr("Nodes..."),this);
    connect(nodeAction,SIGNAL(triggered()),this,SLOT(viewNode()));
    employeeAction = new QAction(tr("Employee..."),this);
    connect(employeeAction,SIGNAL(triggered()),this,SLOT(viewEmployee()));
    subdivisionAction = new QAction(tr("Subdivision..."),this);
    connect(subdivisionAction,SIGNAL(triggered()),this,SLOT(viewSubdivision()));
    postAction = new QAction(tr("Post..."),this);
    connect(postAction,SIGNAL(triggered()),this,SLOT(viewPost()));
    medicalService = new QAction(tr("Medical Service..."),this);
    connect(medicalService,SIGNAL(triggered()),this,SLOT(viewMedicalService()));
    treatmentAction = new QAction(tr("Treatment..."),this);
    connect(treatmentAction,SIGNAL(triggered()),this,SLOT(viewTreatment()));
    diseaseAction = new QAction(tr("Disease..."),this);
    connect(diseaseAction,SIGNAL(triggered()),this,SLOT(viewDisease()));
    locationActon = new QAction(tr("Location..."),this);
    connect(locationActon,SIGNAL(triggered()),this,SLOT(viewLocation()));
    typeOfWorkAction = new QAction(tr("Type Of Work..."),this);
    connect(typeOfWorkAction,SIGNAL(triggered()),this,SLOT(viewTypeOfWork()));
    preparationAction = new QAction(tr("Preparation..."),this);
    connect(preparationAction,SIGNAL(triggered()),this,SLOT(viewPreparation()));

    //Documents Action
    preparationDocAction = new QAction(tr("Preparation Document..."),this);
    connect(preparationDocAction,SIGNAL(triggered()),this,SLOT(viewPreparationDoc()));

    //Reports Action

    //Service Action
    //prefixAction = new QAction(tr("Prefix..."),this);
    //connect(prefixAction,SIGNAL(triggered()),this,SLOT(prefixFunction()));

    putAction = new QAction(tr("Put Base on FTP"),this);
    connect(putAction,SIGNAL(triggered()),this,SLOT(putBaseProcedure()));

    getAction = new QAction(tr("Get Base from FTP"),this);
    connect(getAction,SIGNAL(triggered()),this,SLOT(getBaseProcedure()));

    searchAction = new QAction(tr("Search In Journal By Contens..."),this);
    connect(searchAction,SIGNAL(triggered()),this,SLOT(searchProcedure()));

    exchangeAction = new QAction(tr("Exchange Data Base..."),this);
    connect(exchangeAction,SIGNAL(triggered()),this,SLOT(exchangeData()));

    //Help Action
    aboutQtAction = new QAction(tr("About Qt..."),this);
    connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    aboutProgAction = new QAction(tr("About programm..."),this);
    connect(aboutProgAction,SIGNAL(triggered()),this,SLOT(aboutProgramm()));
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    menuBar()->setStyleSheet("font: bold; color: darkblue;");
    fileMenu->addAction(prefixAction);
    fileMenu->addAction(exitAction);

    referenceMenu = menuBar()->addMenu(tr("References"));
    referenceMenu->addAction(organizationAction);
    referenceMenu->addAction(employeeAction);
    referenceMenu->addAction(subdivisionAction);
    referenceMenu->addAction(postAction);
    referenceMenu->addSeparator();
    referenceMenu->addAction(preparationAction);
    referenceMenu->addAction(medicalService);
    //referenceMenu->addAction(treatmentAction);
    referenceMenu->addAction(diseaseAction);
    referenceMenu->addAction(typeOfWorkAction);
    referenceMenu->addAction(locationActon);
    referenceMenu->addSeparator();
    referenceMenu->addAction(nodeAction);
    referenceMenu->addSeparator();

    documentMenu = menuBar()->addMenu(tr("Documents"));
    documentMenu->addAction(preparationDocAction);
    documentMenu->addSeparator();

    reportMenu = menuBar()->addMenu(tr("Reports"));
    reportMenu->addSeparator();

    serviceMenu = menuBar()->addMenu(tr("Service"));
    //serviceMenu->addAction(prefixAction);
    serviceMenu->addAction(putAction);
    serviceMenu->addAction(getAction);
    serviceMenu->addSeparator();
    serviceMenu->addAction(searchAction);
    serviceMenu->addSeparator();
    serviceMenu->addAction(exchangeAction);

    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutQtAction);
    helpMenu->addAction(aboutProgAction);

}

void MainWindow::aboutProgramm()
{
    QSettings iniSettings("MSO.ini",QSettings::IniFormat);
    QString version = iniSettings.value("Version").toString();
    //    int fontId = iniSettings.value("Font").toInt();

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("MSO"));
    QPixmap pixLogo(":/logo.png");
    msgBox.setIconPixmap(pixLogo);
    QString textMessage = tr("<p style=\"color:darkblue\"; style=\"font-family:Times New Roman\"; "
                             "style=\"font-size :20pt\"; "
                             "style=\"font: bold\" >"
                             "MSO "
                             "<br/> (SQLite version) ");
    textMessage += version;
    textMessage += tr("</p>"
                      "<p style=\"color:darkgreen\"; style=\"font-family:Times New Roman\"; "
                      "style=\"font-size :12pt\">Copyright 2011-15 A+O Batrakov Inc.</p>"
                      "<p style=\"font-size :12pt\">"
                      "The program helps to keep MSO information.</p>"
                      "<p style=\"font-family:Times New Roman\"; style=\"font-size :10pt\">"
                      "An how to improve, extend the functionality of the program, press button "
                      "\"Send mail\"");
    msgBox.setText(textMessage);
    //msgBox.setFont(QFont(QFontDatabase::applicationFontFamilies(fontId).first()));
    QPushButton *sendM = new QPushButton(tr("Send mail\nto developer"));
    sendM->setStyleSheet("QPushButton {font: yellow}");
    msgBox.addButton(QMessageBox::Ok);
    msgBox.addButton(sendM,QMessageBox::AcceptRole);
    msgBox.exec();
    if(msgBox.clickedButton() == sendM){
        sendMail();
    }else{
        msgBox.close();
    }
}

void MainWindow::splitterCreate()
{
    splitter = new QSplitter(Qt::Horizontal);
    splitter->setFrameStyle(QFrame::StyledPanel);
    splitter->addWidget(panel);
    splitter->setStretchFactor(1,1);
    setCentralWidget(splitter);
}

void MainWindow::createContextMenu()
{
    addAction = new QAction(tr("Add Record"),this);
    QPixmap pixAdd(":/add.png");
    addAction->setIcon(pixAdd);
    connect(addAction,SIGNAL(triggered()),this,SLOT(addRecordOfTable()));

    QPixmap pixDelete(":/delete.png");
    deleteAction = new QAction(tr("Delete Record"),this);
    deleteAction->setIcon(pixDelete);
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteRecordOfTable()));

    QPixmap pixEdit(":/edit.png");
    editAction = new QAction(tr("Edit Record"),this);
    editAction->setIcon(pixEdit);
    connect(editAction,SIGNAL(triggered()),this,SLOT(editRecordOfTable()));

    //QPixmap pixEdit(":/edit.png");
    copyAction = new QAction(tr("Copy Record"),this);
    //editAction->setIcon(pixEdit);
    connect(copyAction,SIGNAL(triggered()),this,SLOT(copyRecordOfTable()));

    tableView->addAction(addAction);
    tableView->addAction(deleteAction);
    tableView->addAction(editAction);
    tableView->addAction(copyAction);
    tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::viewTemplateTable(QString tempTable)
{
//    if(!tableView->isVisible()){
//        tableView->setVisible(true);
//    }
    if(tableView->model())
        for(int i=0; i<tableView->model()->columnCount();i++){
            QAbstractItemDelegate* delegate = tableView->itemDelegateForColumn( i );
            //Remove the delegate from the view
            tableView->setItemDelegateForColumn( i, NULL );
            delete delegate;
        }
    tableView->clearSpans();
    templateModel->clear();
    templateModel->setTable(tempTable);

    QString strivgValue;
    bool delAll = false;
    if(tempTable == "node"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Code"));
        templateModel->setHeaderData(2,Qt::Horizontal,tr("Name"));
        templateModel->setHeaderData(3,Qt::Horizontal,tr("Head"));
        if(setFilter){
            templateModel->setFilter(QString("nodename LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Node");
    }else if(tempTable == "post"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        if(setFilter){
            templateModel->setFilter(QString("postname LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Post");
    }else if(tempTable == "subdivision"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        if(setFilter){
            templateModel->setFilter(QString("subdivisionname LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Subdivision");
    }else if(tempTable == "typeofwork"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        if(setFilter){
            templateModel->setFilter(QString("typeofworkname LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Type Of Work");
    }else if(tempTable == "location"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        if(setFilter){
            templateModel->setFilter(QString("locationname LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Location");
    }else if(tempTable == "disease"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        if(setFilter){
            templateModel->setFilter(QString("diseasename LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Disease");
    }else if(tempTable == "treatment"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        if(setFilter){
            templateModel->setFilter(QString("treatmentname LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Treatment");
    }else if(tempTable == "medicalservice"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        templateModel->setHeaderData(2,Qt::Horizontal,tr("Cost"));
        if(setFilter){
            templateModel->setFilter(QString("medicalservicename LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Medical Service");
    }else if(tempTable == "employee"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("FIO"));
        templateModel->setHeaderData(2,Qt::Horizontal,tr("Organization"));
        templateModel->setRelation(2,QSqlRelation("organization","organizationid","organizationname"));
        templateModel->setHeaderData(3,Qt::Horizontal,tr("Subdivision"));
        templateModel->setRelation(3,QSqlRelation("subdivision","subdivisionid","subdivisionname"));
        templateModel->setHeaderData(4,Qt::Horizontal,tr("Post"));
        templateModel->setRelation(4,QSqlRelation("post","postid","postname"));
        templateModel->setHeaderData(5,Qt::Horizontal,tr("Data Birthday"));
        if(setFilter){
            templateModel->setFilter(QString("employeename LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Employee");
    }else if(tempTable == "organization"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        if(setFilter){
            templateModel->setFilter(QString("organizationname LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Organization");
    }else if(tempTable == "preparation"){
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
        templateModel->setHeaderData(2,Qt::Horizontal,tr("Cost"));
        templateModel->setHeaderData(3,Qt::Horizontal,tr("Expi"));
        if(setFilter){
            templateModel->setFilter(QString("organizationname LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Organization");
    }else if(tempTable == "treatmentdoc"){
        templateModel->setHeaderData(0,Qt::Horizontal,tr("Number"));
        templateModel->setHeaderData(1,Qt::Horizontal,tr("Date"));
        templateModel->setHeaderData(2,Qt::Horizontal,tr("FIO"));
        templateModel->setRelation(2,QSqlRelation("employee","employeeid","employeename"));
        if(setFilter){
            templateModel->setFilter(QString("employeename LIKE '%%1%'").arg(filterTable));
        }
        strivgValue = tr("Treatment Doc");
    }
    if(!delAll){
        templateModel->select();
        QHeaderView *head = tableView->horizontalHeader();
        connect(head,SIGNAL(sectionClicked(int)),this,SLOT(sortTable(int)));
        tableView->setModel(templateModel);
        if(tempTable == "treatmentdoc" || tempTable == "nodes" || tempTable == "contractdoc"){
            tableView->setColumnHidden(0, false);
        }else{
            tableView->setColumnHidden(0, true);
        }

        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        if(tempTable == "node"){
            tableView->setItemDelegateForColumn(3,new BoolItemDelegate(this));
            //templateModel->record().
        }
        tableView->setAlternatingRowColors(true);
        tableView->resizeColumnsToContents();
        //tableView->sizeHintForColumn(int);
        tableView->horizontalHeader()->setResizeContentsPrecision(1000);
        head->setStretchLastSection(true);
        tableLabel->clear();
        tableLabel->setText(tr("Name of Table: %1").arg(strivgValue));
        tableLabel->setStyleSheet("font: bold; color: darkblue;");
        setFilter = false;
    }
}

void MainWindow::sortTable(int index)
{
    templateModel->setSort(index,Qt::AscendingOrder);
    templateModel->select();
}

void MainWindow::updatePanel(QModelIndex inDex)
{
    templateModel->select();
    tableView->resizeColumnsToContents();
    QHeaderView *head = tableView->horizontalHeader();
    head->setStretchLastSection(true);
    tableView->setCurrentIndex(inDex);
}

void MainWindow::addRecordOfTable()
{
    QString valueTemp = templateModel->tableName();
    if(valueTemp == "node"){
        NodeForm form("",this,false);
        form.exec();
    }else if(valueTemp == "post"){
        PostForm form("",this,false);
        form.exec();
    }else if(valueTemp == "subdivision"){
        SubdivisionForm form("",this,false);
        form.exec();
    }else if(valueTemp == "typeofwork"){
        TypeOfWorkForm form("",this,false);
        form.exec();
    }else if(valueTemp == "location"){
        LocationForm form("",this,false);
        form.exec();
    }else if(valueTemp == "disease"){
        DiseaseForm form("",this,false);
        form.exec();
    }else if(valueTemp == "treatment"){
        TreatmentForm form("",this,false);
        form.exec();
    }else if(valueTemp == "medicalservice"){
        MedicalServiceForm form("",this,false);
        form.exec();
    }else if(valueTemp == "employee"){
        EmployeeForm form("",this,false);
        form.exec();
    }else if(valueTemp == "organization"){
        OrganizationForm form("",this,false);
        form.exec();
    }else if(valueTemp == "preparation"){
        PreparationForm form("",this,false);
        form.exec();
    }else if(valueTemp == "treatmentdoc"){
        TreatmentDocForm form("",this,false);
        form.exec();
    }
    QModelIndex modIndex = tableView->currentIndex();
    MainWindow::updatePanel(modIndex);
}

void MainWindow::deleteRecordOfTable()
{
    QModelIndex index = tableView->currentIndex();
    if(index.isValid()){
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
            QString valueTemp, iDValue;
            valueTemp = templateModel->tableName();
            QModelIndex index = tableView->currentIndex();
            QSqlRecord record = templateModel->record(index.row());
            if(valueTemp == "node"){
                iDValue = record.value("nodeid").toString();
                NodeForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "post"){
                iDValue = record.value("postid").toString();
                PostForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "subdivision"){
                iDValue = record.value("subdivisionid").toString();
                SubdivisionForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "typeofwork"){
                iDValue = record.value("typeofworkid").toString();
                TypeOfWorkForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "location"){
                iDValue = record.value("locationid").toString();
                LocationForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "disease"){
                iDValue = record.value("diseaseid").toString();
                DiseaseForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "treatment"){
                iDValue = record.value("treatmentid").toString();
                TreatmentForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "medicalservice"){
                iDValue = record.value("medicalserviceid").toString();
                MedicalServiceForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "employee"){
                iDValue = record.value("employeeid").toString();
                EmployeeForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "organization"){
                iDValue = record.value("organizationid").toString();
                OrganizationForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "preparation"){
                iDValue = record.value("preparatioid").toString();
                PreparationForm form(iDValue,this,false);
                form.deleteRecord();
            }else if(valueTemp == "treatmentdoc"){
                iDValue = record.value("treatmentdocid").toString();
                TreatmentDocForm form(iDValue,this,false);
                form.deleteRecord();
            }
        }
    }
    updatePanel(index);
}

void MainWindow::editRecordOfTable()
{
    QString stringVar = templateModel->tableName();
    QModelIndex index = tableView->currentIndex();
    if(index.isValid()){
        QSqlRecord record =templateModel->record(index.row());
        if(stringVar == "node"){
            QString iD = record.value("nodeid").toString();
            NodeForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "post"){
            QString iD = record.value("postid").toString();
            PostForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "subdivision"){
            QString iD = record.value("subdivisionid").toString();
            SubdivisionForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "typeofwork"){
            QString iD = record.value("typeofworkid").toString();
            TypeOfWorkForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "location"){
            QString iD = record.value("locationid").toString();
            LocationForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "disease"){
            QString iD = record.value("diseaseid").toString();
            DiseaseForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "treatment"){
            QString iD = record.value("treatmentid").toString();
            TreatmentForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "medicalservice"){
            QString iD = record.value("medicalserviceid").toString();
            MedicalServiceForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "employee"){
            QString iD = record.value("employeeid").toString();
            EmployeeForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "organization"){
            QString iD = record.value("organizationid").toString();
            OrganizationForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "preparation"){
            QString iD = record.value("preparationid").toString();
            PreparationForm form(iD, this, false);
            form.exec();
        }else if(stringVar == "treatmentdoc"){
            QString iD = record.value("treatmendoctid").toString();
            TreatmentDocForm form(iD, this, false);
            form.exec();
        }
    }

    QModelIndex modIndex = tableView->currentIndex();
    MainWindow::updatePanel(modIndex);
}

void MainWindow:: copyRecordOfTable()
{
    QMessageBox::warning(this,tr("Atention!"),tr("This menu item does not work."));
}

void MainWindow::putBaseProcedure()
{
    PutBase putBase(this);
    putBase.putBase();
    //QMessageBox::warning(this,tr("Atention!"),tr("This menu item does not work."));
}

void MainWindow::getBaseProcedure()
{
    GetBase getBase(this);
    getBase.getBaseHttp();
    //QMessageBox::warning(this,tr("Atention!"),tr("This menu item does not work."));
}

void MainWindow::searchProcedure()
{
    QString valueTempModel = templateModel->tableName();

    SearchForm searchForm(valueTempModel, this);
    searchForm.exec();
    filterTable = searchForm.rowOut();
    setFilter = true;

    viewTemplateTable(valueTempModel);
    //QMessageBox::warning(this,tr("Atention!"),tr("This menu item does not work."));
}

void MainWindow::exchangeData()
{
    ExchangeForm openForm(this);
    openForm.exec();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    writeSettings();
    if(fileExchange.size() == 0){
        fileExchange.remove();
    }else{
        QSettings settings("AO_Batrakov_Inc.", "MSO");
        if(settings.value("Send").toBool() == false){
            fileExchange.close();
        }else{
            settings.remove("Send");
            fileExchange.close();
            QFile fileDel("exchange.txt");
            fileDel.remove();
        }
    }
}

void MainWindow::sendMail()
{
    SmtpForm formS(this);
    formS.exec();
}

void MainWindow::prefixForm()
{
    PrefixNumber openForm(this);
    openForm.exec();
}

void MainWindow::viewNode()
{
    viewTemplateTable("node");
}

void MainWindow::viewEmployee()
{
    viewTemplateTable("employee");
}

void MainWindow::viewPost()
{
    viewTemplateTable("post");
}

void MainWindow::viewSubdivision()
{
    viewTemplateTable("subdivision");
}

void MainWindow::viewMedicalService()
{
    viewTemplateTable("medicalservice");
}

void MainWindow::viewTreatment()
{
    viewTemplateTable("treatment");
}

void MainWindow::viewDisease()
{
    viewTemplateTable("disease");
}

void MainWindow::viewLocation()
{
    viewTemplateTable("location");
}

void MainWindow::viewTypeOfWork()
{
    viewTemplateTable("typeofwork");
}

void MainWindow::viewOrganization()
{
    viewTemplateTable("organization");
}

void MainWindow::viewPreparation()
{
    viewTemplateTable("preparation");
}

void MainWindow::viewPreparationDoc()
{
    viewTemplateTable("treatmentdoc");
}
