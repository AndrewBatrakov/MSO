#ifndef MEDICALSERVICEFORM_H
#define MEDICALSERVICEFORM_H

#include <QtWidgets>
#include "lineedit.h"

class MedicalServiceForm : public QDialog
{
    Q_OBJECT

public:
    MedicalServiceForm(QString, QWidget *, bool);
    void done(int result);
    QString rowOut() const {return indexTemp;};

public slots:
    void deleteRecord();

private slots:
    void editRecord();
    void readSettings();
    void writeSettings();

private:
    QLabel *labelName;
    LineEdit *editName;
    QLabel *labelCost;
    QDoubleSpinBox *editCost;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QString indexTemp;
    QFile exchangeFile;
};

#endif // MEDICALSERVICEFORM_H
