#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <QPoint>
#include <functional>
#include <vector>
#include <QMatrix4x4>



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

class Formula
{
    Formula();
    void setRotate(double ax, double ay, double az);
    void addRotate(double ax, double ay, double az);
    void setScale(double kx, double ky, double kz);
    void addScale(double kx, double ky, double kz);
public:
    QMatrix4x4 transform;
    std::function<double(double, double)> f;
};



#endif // PRIMITIVES_H
