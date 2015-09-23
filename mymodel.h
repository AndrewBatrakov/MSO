#ifndef MYMODEL_H
#define MYMODEL_H

#include <QtSql>

class MyModel : public QSqlRelationalTableModel {
    Q_OBJECT
public:
    MyModel(QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const;
};

#endif // MYMODEL_H
