#ifndef PREPARATIONFORM_H
#define PREPARATIONFORM_H

#include <QtWidgets>
#include "lineedit.h"

class PreparationForm : public QDialog
{
    Q_OBJECT

public:
    PreparationForm(QString, QWidget *, bool);
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
    QLabel *labelExpirationDate;
    QDateEdit *editExpirationDate;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;

    QString indexTemp;
    QFile exchangeFile;
};

#endif // PREPARATIONFORM_H
