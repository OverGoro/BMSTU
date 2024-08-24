#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <QPoint>
#include <vector>




class Line
{
public:
    Line() {}
    Line(QPoint p_1, QPoint p_2);;
    QPoint getFirstPoint();
    QPoint getSecondPoint();
    QPointF solve_intersection(const Line &other);
    int x(int y);
    int y(int x);
public:
    int x_1, y_1, x_2, y_2;
    double a,b,c;
};

class Figure
{
public:
    Figure(){points = std::vector<QPoint>();}
    Figure(const std::vector<QPoint> &points)
        :points(points){}
    ~Figure() = default;
    std::vector<QPoint> getPoints() const;
    std::vector<Line> getLines() const;
    void addPoint(QPoint point);
    void addPoint(int x, int y);
public:
    std::vector<QPoint> points;
    static int getMinX(const std::vector<Figure> &figures);
    static int getMinY(const std::vector<Figure> &figures);
    static int getMaxX(const std::vector<Figure> &figures);
    static int getMaxY(const std::vector<Figure> &figures);
};



#endif // PRIMITIVES_H
