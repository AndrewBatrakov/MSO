#ifndef TREATMENTFORM_H
#define TREATMENTFORM_H

#include <QtWidgets>
#include "lineedit.h"

class TreatmentForm : public QDialog
{
    Q_OBJECT

public:
    TreatmentForm(QString, QWidget *, bool);
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
    LineEdit *editCost;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QString indexTemp;
    QFile exchangeFile;
};

#endif // TREATMENTFORM_H
