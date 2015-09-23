#ifndef POSTFORM_H
#define POSTFORM_H

#include <QtWidgets>
#include "lineedit.h"

class PostForm : public QDialog
{
    Q_OBJECT

public:
    PostForm(QString, QWidget *, bool);
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

#endif // POSTFORM_H
