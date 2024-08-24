#include "ScalePerspectiveCameraAdapter.h"
#include "ScalePointAdapter.h"
ScalePerspectiveCameraAdapter::ScalePerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &camera, const ScaleParams &params)
{
    this->camera = camera;
    this->params = params;
}

void ScalePerspectiveCameraAdapter::request()
{
    ScalePointAdapter(std::shared_ptr<Point>(&camera->_position_point, [](Point *){}), params).request();
    ScalePointAdapter(std::shared_ptr<Point>(&camera->_direction_point, [](Point *){}), params).request();
    ScalePointAdapter(std::shared_ptr<Point>(&camera->_up_point, [](Point *){}), params).request();
}
