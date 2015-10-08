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

    void addOrgRecord();
    void seeOrgRecord();
    void listOrgRecord();
    void addSubRecord();
    void seeSubRecord();
    void listSubRecord();
    void addPostRecord();
    void seePostRecord();
    void listPostRecord();

private:
    QLabel *labelFIO;
    LineEdit *editFIO;
    QLabel *labelOrg;
    LineEdit *editOrg;
    QLabel *labelSub;
    LineEdit *editSub;
    QLabel *labelPost;
    LineEdit *editPost;
    QLabel *labelDate;
    QDateEdit *editDate;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QString indexTemp;
    QFile exchangeFile;
};

#endif // EMPLOYEEFORM_H
