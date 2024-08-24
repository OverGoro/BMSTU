#include "ScalePointAdapter.h"
#include "ScalePolygonAdapter.h"

void ScalePolygonAdapter::request()
{
    ScalePointAdapter(std::shared_ptr<Point>(&polygon->_p1, [](Point *){}), params).request();
    ScalePointAdapter(std::shared_ptr<Point>(&polygon->_p2, [](Point *){}), params).request();
    ScalePointAdapter(std::shared_ptr<Point>(&polygon->_p3, [](Point *){}), params).request();
}
