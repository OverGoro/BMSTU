#ifndef TABLEITEMDELEGATE_H
#define TABLEITEMDELEGATE_H

#include <QItemDelegate>
class TableItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TableItemDelegate(QObject *parent = 0);

protected:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // TABLEITEMDELEGATE_H
