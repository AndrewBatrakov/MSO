#include "dbdirection.h"

DBDirection::DBDirection(QWidget *parent) :
    QDialog(parent)
{

}

bool DBDirection::connectDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MSO.dat");
    if(!db.open()){
        QMessageBox::warning(0,QObject::tr("QSQLite Database Error"),
                             db.lastError().text());
        return false;
    }else{
        return true;
    }

}
