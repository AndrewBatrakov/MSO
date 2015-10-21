#include "tableenterdelegate.h"
#include <QtSql>

TableEnterDelegate::TableEnterDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *TableEnterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    QLineEdit *nameEdit = new QLineEdit(parent);
    QCompleter *nameCompleter = new QCompleter();
    QSqlQueryModel *nameModel = new QSqlQueryModel(nameCompleter);
    nameModel->setQuery("SELECT DISTINCT employeename FROM employee order by employeeid desc LIMIT 500");
    nameCompleter->setModel(nameModel);
    m_plineEdit = nameEdit;
    m_defaultRect = option.rect;
    m_plineEdit->text().toUpper();
    connect(nameEdit,SIGNAL(textChanged(QString)),this,SLOT(resizeLineEditToContents()));
    connect(nameEdit,SIGNAL(textEdited(const QString &)),SLOT(toUpper(const QString &)));
    nameEdit->setMaxLength(45);
    return nameEdit;
}

void TableEnterDelegate::resizeLineEditToContents()
{
    QString text = m_plineEdit->text();
    if(text != ""){
        QFontMetrics fm = m_plineEdit->fontMetrics();
        int w = fm.boundingRect(text).width() + fm.maxWidth();
        if(w>= m_defaultRect.width()){
            m_plineEdit->resize(w,m_plineEdit->height());
        }
    }
}

void TableEnterDelegate::toUpper(const QString &text)
{
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if(le)
        return;
    le->setText(text.toUpper());
}

void TableEnterDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *le = qobject_cast<QLineEdit *>(editor);
    le->setText(value);
}

void TableEnterDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *le = qobject_cast<QLineEdit *>(editor);
    QString text = le->text();
    model->setData(index,text);
    return;
}
