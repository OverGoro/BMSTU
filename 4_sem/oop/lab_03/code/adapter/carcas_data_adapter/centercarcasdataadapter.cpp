#include "centercarcasdataadapter.h"
#include <algorithm>
void CenterCarcasDataAdapter::request()
{
    Point tmp_p(0,0,0);
    double min_x, min_y, min_z;
    double max_x, max_y, max_z;
    if (carcas_data->points.size() > 0)
    {
        min_x = max_x = carcas_data->points.begin()->getX();
        min_y = max_y = carcas_data->points.begin()->getY();
        min_z = max_z = carcas_data->points.begin()->getZ();
        for (auto p : carcas_data->points)
        {
            min_x = std::min(min_x, p.getX());
            min_y = std::min(min_y, p.getY());
            min_z = std::min(min_z, p.getZ());
            max_x = std::max(max_x, p.getX());
            max_y = std::max(max_y, p.getY());
            max_z = std::max(max_z, p.getZ());
        }
        tmp_p = Point((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
    }
    *center = tmp_p;
}
