#include "polygon.h"

Polygon::Polygon() {}

Polygon::Polygon(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    _p1 = {x1, y1, z1};
    _p2 = {x2, y2, z2};
    _p3 = {x3, y3, z3};
}

Polygon::Polygon(const Point &p1, const Point &p2, const Point &p3)
{
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;
}
