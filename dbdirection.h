#ifndef DBDIRECTION_H
#define DBDIRECTION_H

#include <QtWidgets>
#include <QtSql>

class DBDirection : public QDialog
{
    Q_OBJECT
public:
    DBDirection(QWidget *parent = 0);

    bool connectDataBase();

private:
    QSqlDatabase db;
};

#endif // DBDIRECTION_H
