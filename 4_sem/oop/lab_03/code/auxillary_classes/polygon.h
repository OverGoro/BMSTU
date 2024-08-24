#ifndef POLYGON_H
#define POLYGON_H
#include "Point.h"

class Polygon
{
    friend class MovePolygonAdapter;
    friend class ScalePolygonAdapter;
    friend class RotatePolygonAdapter;
    friend class DrawPolygonAdapter;
    friend class CenterPolygonDataAdapter;
public:
    Polygon();
    Polygon(double x1, double y1, double z1,
            double x2, double y2, double z2,
            double x3, double y3, double z3);
    Polygon(const Point &p1, const Point &p2, const Point &p3);
    ~Polygon(){};
protected:
    Point _p1, _p2, _p3;
};

#endif // POLYGON_H
