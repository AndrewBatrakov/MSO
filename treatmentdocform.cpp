#include "treatmentdocform.h"
#include <QtSql>

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
    connect(editFIO,SIGNAL(editingFinished()),this,SLOT(fioChange()));

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

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelNumberDoc,0,0);
    mainLayout->addWidget(editNumberDoc,0,1);
    mainLayout->addWidget(labelDateDoc,1,0);
    mainLayout->addWidget(editDateDoc,1,1);
    mainLayout->addWidget(labelFIO,2,0);
    mainLayout->addLayout(empLayout,2,1);
    mainLayout->addWidget(labelOrg,3,0);
    mainLayout->addWidget(editOrg,3,1);
    mainLayout->addWidget(labelSub,4,0);
    mainLayout->addWidget(editSub,4,1);
    mainLayout->addWidget(labelPost,5,0);
    mainLayout->addWidget(editPost,5,1);
    if(!onlyForRead){
        mainLayout->addWidget(buttonBox,6,1);
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

}

void TreatmentDocForm::editRecord()
{

}

void TreatmentDocForm::done(int result)
{
    exchangeFile.close();
    writeSettings();
    QDialog::done(result);
}

void TreatmentDocForm::readSettings()
{

}

void TreatmentDocForm::writeSettings()
{

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
    QSqlQuery query;
    query.prepare("SELECT ");
}
