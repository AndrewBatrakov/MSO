#ifndef TREATMENTDOC_H
#define TREATMENTDOC_H

#include <QtWidgets>
#include "lineedit.h"
#include <QtSql>

class NonEditTableColumnDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    NonEditTableColumnDelegate(QObject * parent = 0) : QItemDelegate(parent) {}
    virtual QWidget * createEditor ( QWidget *, const QStyleOptionViewItem &,
                                     const QModelIndex &) const
    {
        return 0;
    }
};

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

    void addRecordOfTable();
    void deleteRecordOfTable();
    void editRecordOfTable();

    void changeItemService(int, int);
    void changeItemPreparation(int, int);

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
    QLabel *labelItogoService;
    QLabel *editItogoService;
    QLabel *labelItogoPreparation;
    QLabel *editItogoPreparation;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QTableWidget *medicalServiceWidget;
    QTableWidget *preparationWidget;
    QTabWidget *tabWidget;

    QString indexTemp;

    QFile exchangeFile;
};

#endif // TREATMENTDOC_H
