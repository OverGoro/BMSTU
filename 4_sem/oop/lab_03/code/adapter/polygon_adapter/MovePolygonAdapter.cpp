#include "MovePointAdapter.h"
#include "MovePolygonAdapter.h"

void MovePolygonAdapter::request()
{
    MovePointAdapter(std::shared_ptr<Point>(&polygon->_p1, [](Point *){}), params).request();
    MovePointAdapter(std::shared_ptr<Point>(&polygon->_p2, [](Point *){}), params).request();
    MovePointAdapter(std::shared_ptr<Point>(&polygon->_p3, [](Point *){}), params).request();
}
