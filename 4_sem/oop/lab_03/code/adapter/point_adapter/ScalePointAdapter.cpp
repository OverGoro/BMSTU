#include "ScalePointAdapter.h"
#include "MovePointAdapter.h"
void ScalePointAdapter::request()
{
    MovePointAdapter(point, MoveParams(- params.getCenter().getX(),
                                       - params.getCenter().getY(),
                                       - params.getCenter().getZ())).request();
    point->setX(point->getX() * params.getKx());
    point->setY(point->getY() * params.getKy());
    point->setZ(point->getZ() * params.getKz());
    MovePointAdapter(point, MoveParams(params.getCenter().getX(),
                                       params.getCenter().getY(),
                                       params.getCenter().getZ())).request();
}
