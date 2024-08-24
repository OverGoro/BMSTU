#ifndef FIGUREMODEL_H
#define FIGUREMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include "painterwidget.h"
#include "exceptions.h"

class FigureModel : public QAbstractTableModel
{
    Q_OBJECT
protected:
    Figure getFigure(const QModelIndex &index);
    int rowCount() const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount() const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
public:
    explicit FigureModel(QObject *parent = nullptr);
    void setFigures(const std::vector<Figure> &figures);
    std::vector<Figure> getOpenedFigures();
    std::vector<Figure> getClosedFigures();
    void addPoint(QPoint p);
    void closeFigure();
    void clear();
    void pop();
protected:
    std::vector<Figure> figures;
};

#endif // FIGUREMODEL_H
