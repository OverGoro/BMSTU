#include "MovePerspectiveCameraAdapter.h"
#include <PerspectiveCamera.h>
#include "MovePointAdapter.h"
MovePerspectiveCameraAdapter::MovePerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &cam, const MoveParams &params)
{
    camera = cam;
    this->params = params;
}

void MovePerspectiveCameraAdapter::request()
{
    MovePointAdapter(std::shared_ptr<Point>(&camera->_position_point, [](Point *){}), params).request();
    MovePointAdapter(std::shared_ptr<Point>(&camera->_direction_point, [](Point *){}), params).request();
    MovePointAdapter(std::shared_ptr<Point>(&camera->_up_point, [](Point *){}), params).request();
}
