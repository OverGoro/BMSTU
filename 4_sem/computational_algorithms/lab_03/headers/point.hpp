#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

class Point
{
private:
    double x, y;

public:
    Point() = default;
    Point(double x = 0, double y = 0)
        :x(x), y(y){}
    double getX() const noexcept
    {
        return x;
    }
    double getY() const noexcept
    {
        return y;
    }
    void setX(double v) noexcept
    {
        x = v;
    }
    void setY(double v) noexcept
    {
        y = v;
    }
    void print(std::ostream &os = std::cout) const
    {
        os << x << " " << y << "\n";
    }
    ~Point() = default;
};

#endif // __POINT_H__