#include "mymodel.h"

MyModel::MyModel(QObject *parent) : QSqlRelationalTableModel(parent)
{

}

Qt::ItemFlags MyModel::flags(
        const QModelIndex &index) const {

    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
//    if (index.column() >= 1 && index.column() < 4)
//        flags |= Qt::ItemIsEditable;
    if (index.column() == 4)
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}

QVariant MyModel::data(
            const QModelIndex &index,
            int role) const {

    QVariant value = QSqlQueryModel::data(index, role);

    switch (role) {

    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == 0)
            return value.toString().prepend(tr("#"));
//        else if (index.column() == 2 && role == Qt::DisplayRole)
//            return value.toDate().toString("dd.MM.yyyy");
//        else if (index.column() == 3 && role == Qt::DisplayRole)
//            return tr("%1")
//                   .arg(value.toDouble(), 0, 'f', 2);
        else if (index.column() == 4)
            return value.toInt() != 0 ? tr("Yes") : tr("No");
        else
            return value;

//    case Qt::TextColorRole:
//        if(index.column() == 1)
//            return qVariantFromValue(QColor(Qt::blue));
//        else
//            return value;

//    case Qt::TextAlignmentRole:
//        if(index.column() == 3)
//            return int(Qt::AlignRight | Qt::AlignVCenter);
//        else if(index.column() == 2 || index.column() == 4)
//            return int(Qt::AlignHCenter | Qt::AlignVCenter);
//        else
//            return int(Qt::AlignHCenter | Qt::AlignVCenter);

//    case Qt::FontRole:
//        if(index.column() == 1) {
//            QFont font = QFont("Helvetica", 10, QFont::Bold);
//            return qVariantFromValue(font);
//        }else
//            return value;

//    case Qt::BackgroundColorRole: {
//        int a = (index.row() % 2) ? 14 : 0;
//        if(index.column() == 0)
//            return qVariantFromValue(QColor(220,240-a,230-a));
//        else if(index.column() == 4)
//            return qVariantFromValue(QColor(200,220-a,255-a));
//        else
//            return value;
//    }
    case Qt::CheckStateRole:
        if (index.column() == 4)
            return (QSqlQueryModel::data(index).toInt() != 0) ?
                    Qt::Checked : Qt::Unchecked;
        else
            return value;

//    case Qt::SizeHintRole:
//        if (index.column() == 0)
//            return QSize(70, 10);
//        if (index.column() == 4)
//            return QSize(60, 10);
//        else
//            return QSize(110, 10);
    }
    return value;
}
