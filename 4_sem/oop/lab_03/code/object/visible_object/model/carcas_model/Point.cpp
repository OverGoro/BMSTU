#include "Point.h"
#include <cmath>
Point::Point(double x, double y, double z)
{
    setX(x);
    setY(y);
    setZ(z);
}

Point::Point(const Point &p)
{
    setX(p.getX());
    setY(p.getY());
    setZ(p.getZ());
}

Point &Point::operator=(const Point &p)
{
    this->setX(p.getX());
    this->setY(p.getY());
    this->setZ(p.getZ());
    return *this;
}

Point::Point(Point &&p)
{
    setX(p.getX());
    setY(p.getY());
    setZ(p.getZ());
}
