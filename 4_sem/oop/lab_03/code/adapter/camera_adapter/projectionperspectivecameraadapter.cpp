#include "projectionperspectivecameraadapter.h"
#include "qdebug.h"

ProjectionPerspectiveCameraAdapter::ProjectionPerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &cam, const std::shared_ptr<Point> &projected, const Point &point)
{
    camera = cam;
    this->projected = projected;
    this->point = point;
}

void ProjectionPerspectiveCameraAdapter::request()
{
    // Векторы камеры
    Point forward = (camera->_direction_point - camera->_position_point); // Направление взгляда камеры
    Point up = (camera->_up_point - camera->_position_point);
    Point right = (Point::calculateNormal(forward, up));

    double k = (camera->_screen_distantion) / Point::length(forward);
    Point on_screen = camera->_position_point + forward * k;

    // qDebug() << on_screen.getX() << on_screen.getY() << on_screen.getZ();

    double z = Point::distanceFromPointToPlane(point, on_screen, up, right);
    k = camera->_screen_distantion / (z + camera->_screen_distantion);
    double x = Point::distanceFromPointToPlane(point, camera->_position_point, forward, up) * k;
    double y = Point::distanceFromPointToPlane(point, camera->_position_point, forward, right) * k;

    // qDebug() << camera->_position_point.getX() << camera->_position_point.getY() << camera->_position_point.getZ();
    // qDebug() << camera->_direction_point.getX() << camera->_direction_point.getY() << camera->_direction_point.getZ();
    // qDebug() << camera->_up_point.getX() << camera->_up_point.getY() << camera->_up_point.getZ();
    // qDebug() << "";
    // qDebug() << forward.getX() << forward.getY() << forward.getZ();
    // qDebug() << up.getX() << up.getY() << up.getZ();
    // qDebug() << right.getX() << right.getY() << right.getZ();




    // Записываем проекцию в объект projected
    projected->setX(x + camera->_screen_distantion * tan(camera->_x_fov / 2));
    projected->setY(y + camera->_screen_distantion * tan(camera->_y_fov / 2));
    projected->setZ(z);

    // qDebug() << "Point: " << point.getX() << point.getY() << point.getZ() << k;
    // qDebug() << "Projected: " <<projected->getX() << projected->getY() << projected->getZ();
    // qDebug() << "";
}

