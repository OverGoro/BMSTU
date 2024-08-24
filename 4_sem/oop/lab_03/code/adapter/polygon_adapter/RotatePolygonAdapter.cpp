#include "RotatePointAdapter.h"
#include "RotatePolygonAdapter.h"
#include <cmath>

void RotatePolygonAdapter::request()
{
    RotatePointAdapter(std::shared_ptr<Point>(&polygon->_p1, [](Point *){}), params).request();
    RotatePointAdapter(std::shared_ptr<Point>(&polygon->_p2, [](Point *){}), params).request();
    RotatePointAdapter(std::shared_ptr<Point>(&polygon->_p3, [](Point *){}), params).request();
}
