#include "primitives.h"

#include "painterexceptions.h"

Line::Line(QPoint p_1, QPoint p_2)
{
    if (p_1.y() > p_2.y())
    {
        x_1 = p_2.x();
        y_1 = p_2.y();
        x_2 = p_1.x();
        y_2 = p_1.y();
    }
    else
    {
        x_1 = p_1.x();
        y_1 = p_1.y();
        x_2 = p_2.x();
        y_2 = p_2.y();
    }
    a = y_1 - y_2;
    b = x_2 - x_1;
    c = x_1 * y_2 - x_2 * y_2;
}

QPoint Line::getFirstPoint()
{
    return QPoint(x_1, y_1);
}
QPoint Line::getSecondPoint()
{
    return QPoint(x_2, y_2);
}

QPointF Line::solve_intersection(const Line &other)
{
    double opr = a * other.b - other.a * b;
    double opr1 = (-c) * other.b - b * (-other.c);
    double opr2 = a * (-other.c) - (-c) * other.a;

    double x = opr1 / opr;
    double y = opr2 / opr;
    return QPointF(x,y);
}

int Line::x(int y)
{
    if (y_1 == y_2) // Если y_1 равен y_2, прямая параллельна оси OY
        return x_1; // В этом случае x не меняется и равен x_1
    double dx = double(x_2 - x_1) / (y_2 - y_1);
    return x_1 + (y - y_1) * dx;
}

int Line::y(int x)
{
    if (x_1 == x_2) // Если x_1 равен x_2, прямая параллельна оси OX
        return y_1; // В этом случае y не меняется и равен y_1
    double dy = double(y_2 - y_1) / (x_2 - x_1);
    return y_1 + (x - x_1) * dy;
}

void Figure::addPoint(int x_1, int y_1)
{
    addPoint(QPoint(x_1, y_1));
}

int Figure::getMinX(const std::vector<Figure> &figures)
{
    bool is_set = false;
    int x = 0;
    for (auto f: figures)
    {
        for (auto p : f.points)
        {
            if (!is_set || p.x() < x)
            {
                x = p.x();
                is_set = true;
            }
        }
    }
    return x;
}

int Figure::getMinY(const std::vector<Figure> &figures)
{
    bool is_set = false;
    int y = 0;
    for (auto f: figures)
    {
        for (auto p : f.points)
        {
            if (!is_set || p.y() < y)
            {
                y = p.y();
                is_set = true;
            }
        }
    }
    return y;
}

int Figure::getMaxX(const std::vector<Figure> &figures)
{
    bool is_set = false;
    int x = 0;
    for (auto f: figures)
    {
        for (auto p : f.points)
        {
            if (!is_set || p.x() > x)
            {
                x = p.x();
                is_set = true;
            }
        }
    }
    return x;
}

int Figure::getMaxY(const std::vector<Figure> &figures)
{
    bool is_set = false;
    int y = 0;
    for (auto f: figures)
    {
        for (auto p : f.points)
        {
            if (!is_set || p.y() > y)
            {
                y = p.y();
                is_set = true;
            }
        }
    }
    return y;
}

std::vector<QPoint> Figure::getPoints() const
{
    return points;
}

std::vector<Line> Figure::getLines() const
{
    std::vector<Line> lines;
    for (int i = 1; i < points.size(); i++)
    {
        lines.push_back(Line(points[i-1], points[i]));
    }
    // lines.push_back(Line(points[0], points[points.size() - 1]));
    return lines;
}

void Figure::addPoint(QPoint p)
{
    points.push_back(p);
}

