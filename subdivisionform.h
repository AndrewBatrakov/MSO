#ifndef SUBDIVISIONFORM_H
#define SUBDIVISIONFORM_H

#include <QtWidgets>
#include "lineedit.h"

class SubdivisionForm : public QDialog
{
    Q_OBJECT

public:
    SubdivisionForm(QString, QWidget *, bool);
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

#endif // SUBDIVISIONFORM_H
