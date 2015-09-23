#ifndef EMPLOYEEFORM_H
#define EMPLOYEEFORM_H

#include <QtWidgets>
#include "lineedit.h"

class EmployeeForm : public QDialog
{
    Q_OBJECT

public:
    EmployeeForm(QString, QWidget *, bool);
    void done(int result);
    QString rowOut() const {return indexTemp;};

public slots:
    void deleteRecord();

private slots:
    void editRecord();
    void readSettings();
    void writeSettings();

private:
    QLabel *labelCode;
    LineEdit *editCode;
    QLabel *labelName;
    LineEdit *editName;
    QCheckBox *head;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QString indexTemp;
    QFile exchangeFile;
};

#endif // EMPLOYEEFORM_H
