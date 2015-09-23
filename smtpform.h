#ifndef SMTPFORM_H
#define SMTPFORM_H

#include <QtWidgets>
#include "lineedit.h"

class SmtpForm : public QDialog
{
    Q_OBJECT

public:
    SmtpForm(QWidget *);
    void done(int result);

private slots:
    void sendText();

private:
    QLabel *labelAbout;
    LineEdit *editAbout;
    LineEdit *editText;

    QPushButton *sendButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;
};

#endif // SMTPFORM_H
