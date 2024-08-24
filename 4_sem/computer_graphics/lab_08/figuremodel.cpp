#include "figuremodel.h"
#include "painterexceptions.h"

FigureModel::FigureModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

void FigureModel::setFigures(const std::vector<Figure> &figures)
{
    this->figures = figures;
}

std::vector<Figure> FigureModel::getOpenedFigures()
{
    std::vector<Figure> opened_figures;
    if (figures.size() > 0)
        opened_figures.push_back(figures.back());
    return opened_figures;
}

std::vector<Figure> FigureModel::getClosedFigures()
{
    std::vector<Figure> closed_figures;
    for (int i = 0; i + 1 < figures.size(); i++)
    {
        auto f = figures[i];
        if (f.points.size() == 0)
            continue;
        if (f.points.size() < 2)
            throw NotAllClosedException();
        closed_figures.push_back(f);
    }
    return closed_figures;
}

void FigureModel::addPoint(QPoint p)
{
    if (figures.size() == 0)
    {
        figures.push_back(Figure());
    }
    figures.back().addPoint(p);
    if (figures.back().points.size() >= 2)
        closeFigure();
    // Определяем начальный и конечный индексы для обновления
    // int firstRow = 0;
    // int lastRow = rowCount() - 1;

    // Уведомляем представление о изменениях в данных
    emit layoutChanged();
    // emit dataChanged(index(firstRow, 0), index(lastRow, columnCount() - 1));
}

void FigureModel::closeFigure()
{
    if (figures.size() == 0)
        throw FewToCloseExcpetion();
    if (figures.back().points.size() < 2)
        throw FewToCloseExcpetion();
    figures.push_back(Figure());
    emit layoutChanged();

}

void FigureModel::clear()
{
    figures.clear();
    emit layoutChanged();
}

void FigureModel::pop()
{
    if (figures.size() == 0)
        return;
    if (figures.back().points.size() == 0)
        figures.pop_back();
    else
        figures.back().points.pop_back();
    emit layoutChanged();
}

int FigureModel::rowCount() const
{
    int rows_num = 0;
    for (auto f : figures)
    {
        rows_num += f.points.size();
        rows_num++;
    }
    if (rows_num > 0)
        rows_num--;
    return rows_num;
}

int FigureModel::rowCount(const QModelIndex &parent) const
{
    return rowCount();
}

int FigureModel::columnCount() const
{
    return 2;
}

int FigureModel::columnCount(const QModelIndex &parent) const
{
    return columnCount();
}

QVariant FigureModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        QString answer = QString("not set");
        if (figures.size() == 0)
        {
            answer = QString("-----");
        }
        else
        {
            int row = index.row();
            for (auto f : figures)
            {
                for (auto p : f.points)
                {
                    if (row == 0)
                    {
                        if (index.column() == 0)
                            answer = QString::number(p.x());
                        else if (index.column() == 1)
                            answer = QString::number(p.y());
                    }
                    row--;
                }
                if (row == 0)
                    answer = QString("-----");
                if (row <= 0)
                    break;
                row--;
            }
        }
        // строкой выше мы формируем ответ. QString::number преобразует число в текст
        return QVariant(answer);
    }
    return QVariant();
}

