#ifndef TREATMENTDOC_H
#define TREATMENTDOC_H

#include <QtWidgets>
#include "lineedit.h"
#include <QtSql>

class TreatmentDocForm : public QDialog
{
    Q_OBJECT
public:
    TreatmentDocForm(QString, QWidget *, bool);
    void done(int result);
    QString rowOut() const {return indexTemp;};

public slots:
    void deleteRecord();

private slots:
    void editRecord();
    void readSettings();
    void writeSettings();

    void addEmpRecord();
    void seeEmpRecord();
    void listEmpRecord();

    void fioChange();

private:
    QLabel *labelNumberDoc;
    LineEdit *editNumberDoc;
    QLabel *labelDateDoc;
    QDateEdit *editDateDoc;
    QLabel *labelFIO;
    LineEdit *editFIO;
    QLabel *labelOrg;
    LineEdit *editOrg;
    QLabel *labelSub;
    LineEdit *editSub;
    QLabel *labelPost;
    LineEdit *editPost;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QTableView *tableView;
    QSqlRelationalTableModel *templateModel;

    QString indexTemp;
    QFile exchangeFile;
};

#endif // TREATMENTDOC_H
