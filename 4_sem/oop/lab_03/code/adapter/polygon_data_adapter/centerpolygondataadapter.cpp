#include "centerpolygondataadapter.h"

void CenterPolygonDataAdapter::request()
{
    Point tmp_p(0,0,0);
    double min_x, min_y, min_z;
    double max_x, max_y, max_z;
    if (Polygon_data->_polygons.size() > 0)
    {
        min_x = max_x = Polygon_data->_polygons.begin()->_p1.getX();
        min_y = max_y = Polygon_data->_polygons.begin()->_p2.getY();
        min_z = max_z = Polygon_data->_polygons.begin()->_p3.getZ();
        for (auto p : Polygon_data->_polygons)
        {
            min_x = std::min(std::min(std::min(min_x, p._p1.getX()), p._p2.getX()), p._p3.getX());
            min_y = std::min(std::min(std::min(min_y, p._p1.getY()), p._p2.getY()), p._p3.getY());
            min_z = std::min(std::min(std::min(min_z, p._p1.getZ()), p._p2.getZ()), p._p3.getZ());
            max_x = std::max(std::max(std::max(max_x, p._p1.getX()), p._p2.getX()), p._p3.getX());
            max_y = std::max(std::max(std::max(max_y, p._p1.getY()), p._p2.getY()), p._p3.getY());
            max_z = std::max(std::max(std::max(max_z, p._p1.getZ()), p._p2.getZ()), p._p3.getZ());
        }
        tmp_p = Point((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
    }
    *center = tmp_p;
}
