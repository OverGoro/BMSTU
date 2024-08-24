#include "MovePointAdapter.h"

void MovePointAdapter::request()
{
    point->setX(point->getX() + params.getDx());
    point->setY(point->getY() + params.getDy());
    point->setZ(point->getZ() + params.getDz());
}