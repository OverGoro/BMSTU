#include "RotatePerspectiveCameraAdapter.h"
#include "RotatePointAdapter.h"
RotatePerspectiveCameraAdapter::RotatePerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &camera, const RotateParams &params)
{
    this->camera = camera;
    this->params = params;
}

void RotatePerspectiveCameraAdapter::request()
{
    RotatePointAdapter(std::shared_ptr<Point>(&camera->_position_point, [](Point *){}), params).request();
    RotatePointAdapter(std::shared_ptr<Point>(&camera->_direction_point, [](Point *){}), params).request();
    RotatePointAdapter(std::shared_ptr<Point>(&camera->_up_point, [](Point *){}), params).request();
}
