#include "pointstableview.h"

PointsTableView::PointsTableView(QWidget *parent)
    : QTableView{parent}
{
    // Установка параметров модели таблицы
    model = new QStandardItemModel(0,2);
    model->setHeaderData(0, Qt::Horizontal, "X");
    model->setHeaderData(1, Qt::Horizontal, "Y");

    // Сигнал при изменении данных модели
    connect(model, &QStandardItemModel::dataChanged, this, [=]{emit this->signalModelDataChanged();});
    connect(model, &QStandardItemModel::itemChanged, this, [=]{emit this->signalModelDataChanged();});

    // Установка модели в таблицу
    setModel(model);

    // Установка ограничителя для пользовательского ввода в таблицу
    itemDelegate = new TableItemDelegate(this);
    setItemDelegate(itemDelegate);

    // Установка параметров контекстного меню для элемента таблицы
    itemContextMenu = new QMenu(this);
    QAction *actionDeletePoint = new QAction();
    actionDeletePoint -> setText (QString ("Удалить"));
    itemContextMenu->addAction(actionDeletePoint);
    connect(itemContextMenu->actions()[0], &QAction::triggered, this, &PointsTableView::slotPointDelete);

    // Установка контекстного меню
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &PointsTableView::customContextMenuRequested, this, &PointsTableView::slotShowContextMenu);

}

void PointsTableView::setData(const QVector<QPointF> &points)
{
    model->setRowCount(points.size());
    horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    for (qsizetype i = 0; i < points.size(); i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(points[i].x(),'g',8)));
        model->setItem(i, 1, new QStandardItem(QString::number(points[i].y(),'g',8)));
    }
    this->update();
}

void PointsTableView::getData(QVector<QPointF> &points)
{
    points.resize(model->rowCount());
    for (qsizetype i = 0; i < model->rowCount(); i++)
    {
        points[i].setX(model->item(i,0)->data(Qt::EditRole).toString().replace(",", ".").toDouble());
        points[i].setY(model->item(i,1)->data(Qt::EditRole).toString().replace(",", ".").toDouble());
    }
}

void PointsTableView::slotShowContextMenu(QPoint pos)
{
    auto index = indexAt(pos);
    if (index.isValid())
    {
        this->curSelectedRow = index.row();
        itemContextMenu->exec(QCursor::pos()); // Позиция, где появляется меню, - это текущая позиция мыши
    }
}

void PointsTableView::slotPointDelete()
{
    if (curSelectedRow < model->rowCount() && curSelectedRow >= 0)
        model->removeRow(curSelectedRow);
    emit signalModelDataChanged();
}

void PointsTableView::slotClear()
{
    model->setRowCount(0);
    emit signalModelDataChanged();
}
