#ifndef __POINT_H__
#define __POINT_H__
#include <cmath>
class Point
{
    friend class MovePointAdapter;
    friend class RotatePointAdapter;
    friend class ScalePointAdapter;
public:
    Point() = default;
    Point(double x, double y, double z);
    Point(const Point &p);
    Point &operator=(const Point &p);
    Point(Point &&p);
    ~Point() = default;

    double getX() const { return x; }
    void setX(double x_) { x = x_; }

    double getY() const { return y; }
    void setY(double y_) { y = y_; }

    double getZ() const { return z; }
    void setZ(double z_) { z = z_; }

    // Функция для нормализации вектора
    static double length(const Point& p)
    {
        return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    }
    static Point normalize(const Point& p)
    {
        double length = Point::length(p);
        return {p.x / length, p.y / length, p.z / length};
    }

    static Point calculateNormal(const Point& a, const Point& b)
    {
        Point normal;
        normal.x = a.y * b.z - a.z * b.y;
        normal.y = a.z * b.x - a.x * b.z;
        normal.z = a.x * b.y - a.y * b.x;
        return normalize(normal);
    }

    static double distanceFromPointToPlane(const Point& point, const Point& planePoint, const Point& vec1, const Point& vec2)
    {
        Point normal = calculateNormal(vec1, vec2);
        double d = -(normal.x * planePoint.x + normal.y * planePoint.y + normal.z * planePoint.z);
        double numerator = (normal.x * point.x + normal.y * point.y + normal.z * point.z + d);
        double denominator = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

        if (denominator == 0.0) {
            // Обработка случая, когда знаменатель равен нулю
            // Можно вернуть бесконечность или другое подходящее значение
            return std::numeric_limits<double>::infinity();
        }

        return numerator / denominator;
    }


    friend Point operator-(const Point &p1, const Point &p2)
    {
        return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
    }

    friend Point operator+(const Point &p1, const Point &p2)
    {
        return Point(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
    }

    friend Point operator*(const Point &p1, const double &alpha)
    {
        return Point(p1.x * alpha, p1.y * alpha, p1.z * alpha);
    }


protected:
    double x;
    double y;
    double z;
};

#endif // __POINT_H__
