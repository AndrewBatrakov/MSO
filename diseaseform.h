#ifndef DISEASEFORM_H
#define DISEASEFORM_H

#include <QtWidgets>
#include "lineedit.h"

class DiseaseForm : public QDialog
{
    Q_OBJECT

public:
    DiseaseForm(QString, QWidget *, bool);
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

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QString indexTemp;
    QFile exchangeFile;
};

#endif // DISEASEFORM_H
