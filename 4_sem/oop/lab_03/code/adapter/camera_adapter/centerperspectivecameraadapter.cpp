#include "centerperspectivecameraadapter.h"

CenterPerspectiveCameraAdapter::CenterPerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &cam, const std::shared_ptr<Point> &center)
{
    this->camera = cam;
    this->center = center;
}

void CenterPerspectiveCameraAdapter::request()
{
    *center = camera->_position_point;
}
