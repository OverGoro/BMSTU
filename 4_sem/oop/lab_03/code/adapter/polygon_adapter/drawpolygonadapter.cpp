#include "drawpolygonadapter.h"
#include "ProjectionAdapterSolution.h"

void DrawPolygonAdapter::request()
{
    auto pp1 = std::make_shared<Point>();
    auto pp2 = std::make_shared<Point>();
    auto pp3 = std::make_shared<Point>();

    ProjectionAdapterSolution().create(camera, pp1, polygon->_p1)->request();
    ProjectionAdapterSolution().create(camera, pp2, polygon->_p2)->request();
    ProjectionAdapterSolution().create(camera, pp3, polygon->_p3)->request();
    // drawer->drawLineWithZBuffer(*pp1, *pp2);
    // qDebug() << pp1->getX() << pp1->getY() << pp2->getX() << pp2->getY();
    if (pp1->getZ() >= 0 && pp2->getZ() >= 0)
        drawer->drawLine(pp1->getX(), pp1->getY(), pp2->getX(), pp2->getY());
    if (pp2->getZ() >= 0 && pp3->getZ() >= 0)
        drawer->drawLine(pp2->getX(), pp2->getY(), pp3->getX(), pp3->getY());
    if (pp3->getZ() >= 0 && pp1->getZ() >= 0)
        drawer->drawLine(pp3->getX(), pp3->getY(), pp1->getX(), pp1->getY());

}
