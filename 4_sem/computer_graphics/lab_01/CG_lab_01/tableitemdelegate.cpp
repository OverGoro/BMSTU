#include "tableitemdelegate.h"

#include <QLineEdit>
#include <QIntValidator>

TableItemDelegate::TableItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *TableItemDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QDoubleValidator *qdv = new QDoubleValidator(-9999999, 9999999, 8);
    qdv->setNotation(QDoubleValidator::StandardNotation);
    editor->setValidator(qdv);
    return editor;
}


void TableItemDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        line->setText(value);
}


void TableItemDelegate::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    QString value = line->text();
    model->setData(index, value);
}


void TableItemDelegate::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
