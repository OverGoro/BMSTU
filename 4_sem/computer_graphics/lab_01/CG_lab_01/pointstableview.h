#ifndef POINTSTABLEVIEW_H
#define POINTSTABLEVIEW_H

#include "tableitemdelegate.h"

#include <QHeaderView>
#include <QVector>
#include <QPointF>
#include <QObject>
#include <QTableView>
#include <QWidget>
#include <QStandardItemModel>
#include <QMenu>

class PointsTableView : public QTableView
{
    Q_OBJECT
private:
    QMenu *itemContextMenu;             // Контекстное меню для элемента
    QStandardItemModel *model;          // Данные таблицы
    TableItemDelegate *itemDelegate;    // Ограничитель входных данных
    qsizetype curSelectedRow;           // Выбранная стркоа матрицы
public:
    explicit PointsTableView(QWidget *parent = nullptr);
    void setData(const QVector<QPointF> &points);
    void getData(QVector<QPointF> &points);
private slots:
    void slotShowContextMenu(QPoint pos);
    void slotPointDelete();
public slots:
    void slotClear();
signals:
    void signalModelDataChanged();
};

#endif // POINTSTABLEVIEW_H
