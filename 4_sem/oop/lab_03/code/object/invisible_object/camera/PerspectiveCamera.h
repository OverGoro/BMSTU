#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "BaseCamera.h"
#include "Point.h"

class PerspectiveCamera : public BaseCamera
{
    friend class MovePerspectiveCameraAdapter;
    friend class ScalePerspectiveCameraAdapter;
    friend class RotatePerspectiveCameraAdapter;
    friend class CenterPerspectiveCameraAdapter;
    friend class ProjectionPerspectiveCameraAdapter;
    friend class PerspectiveCameraBuilder;
    friend class DrawCarcasDataAdapter;

public:
    PerspectiveCamera() = default;
    PerspectiveCamera(const PerspectiveCamera &cam);
    PerspectiveCamera &operator=(const PerspectiveCamera &cam);

    PerspectiveCamera(const Point &position, const Point &direction, const Point &up,
                       double x_fov, double y_fov, double screen_dist)
        : _position_point(position),
        _direction_point(direction),
        _up_point(up),
        _x_fov(x_fov),
        _y_fov(y_fov),
        _screen_distantion(screen_dist){};
    ~PerspectiveCamera() = default;


protected:
    Point _position_point; // Позиция камеры
    Point _direction_point; // Точка на которую смотрит камера
    Point _up_point; // Точка по направлению вверх
    double _x_fov; // Горизонтальный угол зрения
    double _y_fov; // Вертикальный угол зрения
    double _screen_distantion; // Расстояние до экрана
};

#endif // __CAMERA_H__
