#include "PerspectiveCamera.h"
PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera &cam)
{
    _position_point = cam._position_point;
    _direction_point = cam._direction_point;
    _up_point = cam._up_point;
    _x_fov = cam._x_fov;
    _y_fov = cam._y_fov;
    _screen_distantion = cam._screen_distantion;
}

PerspectiveCamera &PerspectiveCamera::operator=(const PerspectiveCamera &cam)
{
    _position_point = cam._position_point;
    _direction_point = cam._direction_point;
    _up_point = cam._up_point;
    _x_fov = cam._x_fov;
    _y_fov = cam._y_fov;
    _screen_distantion = cam._screen_distantion;
    return *this;
}
