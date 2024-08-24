#include "RotatePolygonDataAdapter.h"
#include "polygon_adapter/RotatePolygonAdapter.h"

void RotatePolygonDataAdapter::request()
{
    for (auto &polygon : Polygon_data->_polygons)
    {
        RotatePolygonAdapter(std::shared_ptr<Polygon>(&polygon, [](Polygon *){}), params).request();
    }
}
