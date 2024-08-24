#include "ScalePolygonDataAdapter.h"
#include "polygon_adapter/ScalePolygonAdapter.h"

void ScalePolygonDataAdapter::request()
{
    for (auto &polygon : Polygon_data->_polygons)
    {
        ScalePolygonAdapter(std::shared_ptr<Polygon>(&polygon, [](Polygon *){}), params).request();
    }
}
