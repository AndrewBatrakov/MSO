#ifndef TABLEENTERDELEGATE_H
#define TABLEENTERDELEGATE_H

#include <QtWidgets>

class TableEnterDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TableEnterDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void resizeLineEditToContents();
    void toUpper(const QString &text);

private:
    mutable QLineEdit *m_plineEdit;
    mutable QRect m_defaultRect;
};

#endif // TABLEENTERDELEGATE_H
