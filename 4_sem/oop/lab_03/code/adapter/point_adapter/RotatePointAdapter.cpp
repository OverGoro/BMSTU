#include "RotatePointAdapter.h"
#include "MovePointAdapter.h"
#include <cmath>
void RotatePointAdapter::request()
{
    // Перемещение точки к началу координат
    MovePointAdapter(point, MoveParams(-params.getCenter().getX(),
                                       -params.getCenter().getY(),
                                       -params.getCenter().getZ())).request();

    // Получение углов поворота вокруг каждой из осей
    double angleX = params.getAx();
    double angleY = params.getAy();
    double angleZ = params.getAz();

    // Получение текущих координат точки
    double x = point->getX();
    double y = point->getY();
    double z = point->getZ();

    // Поворот вокруг оси X
    double cosX = cos(angleX);
    double sinX = sin(angleX);
    double y1 = y * cosX - z * sinX;
    double z1 = y * sinX + z * cosX;
    y = y1;
    z = z1;

    // Поворот вокруг оси Y
    double cosY = cos(angleY);
    double sinY = sin(angleY);
    double x1 = x * cosY + z * sinY;
    z1 = -x * sinY + z * cosY;
    x = x1;
    z = z1;

    // Поворот вокруг оси Z
    double cosZ = cos(angleZ);
    double sinZ = sin(angleZ);
    x1 = x * cosZ - y * sinZ;
    y1 = x * sinZ + y * cosZ;
    x = x1;
    y = y1;

    // Установка новых координат точки
    point->setX(x);
    point->setY(y);
    point->setZ(z);

    // Перемещение точки обратно
    MovePointAdapter(point, MoveParams(params.getCenter().getX(),
                                       params.getCenter().getY(),
                                       params.getCenter().getZ())).request();
}
