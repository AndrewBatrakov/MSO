#include "smtpform.h"
#include "smtpssl.h"

SmtpForm::SmtpForm(QWidget *parent) :
    QDialog(parent)
{
    labelAbout = new QLabel(tr("About:"));
    editAbout = new LineEdit;
//    QRegExp regC("[\\x0410-\\x044f 0-9 \" -]{150}");
//    editAbout->setValidator(new QRegExpValidator(regC,this));
    labelAbout->setBuddy(editAbout);

    editText = new LineEdit;

    sendButton = new QPushButton(tr("Send"));
    connect(sendButton,SIGNAL(clicked()),this,SLOT(sendText()));
    sendButton->setToolTip(tr("Send mail Button"));

    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(true);
    cancelButton->setStyleSheet("QPushButton:hover {color: red}");
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    cancelButton->setToolTip(tr("Cancel Button"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(cancelButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(sendButton,QDialogButtonBox::ActionRole);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelAbout,0,0);
    mainLayout->addWidget(editAbout,0,1);
    mainLayout->addWidget(editText,1,0,1,2);
    mainLayout->addWidget(buttonBox,3,1);

    setLayout(mainLayout);

    setWindowTitle(tr("Message to Developer"));
}

void SmtpForm::done(int result)
{
    QDialog::done(result);
}

void SmtpForm::sendText()
{
    Smtp* smtp = new Smtp("hothit@list.ru","AplusO2210","smtp.mail.ru",465);
    QString about = editAbout->text().simplified();
    QString text = editText->text().simplified();
    smtp->sendMail("hothit@list.ru", "hothit@list.ru", about, text);
    emit accept();
}
