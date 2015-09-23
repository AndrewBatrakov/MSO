#ifndef PREFIXNUMBER_H
#define PREFIXNUMBER_H

#include <QtWidgets>
#include "lineedit.h"

class PrefixNumber : public QDialog
{
    Q_OBJECT

public:
    PrefixNumber(QWidget *parent);

private slots:
    void editPN();

private:
    QLabel *labelPrefix;
    LineEdit *editPrefix;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;
};

#endif // PREFIXNUMBER_H
