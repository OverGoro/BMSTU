#include "MovePolygonDataAdapter.h"
#include "polygon_adapter/MovePolygonAdapter.h"

void MovePolygonDataAdapter::request()
{
    for (auto &polygon : Polygon_data->_polygons)
    {
        MovePolygonAdapter(std::shared_ptr<Polygon>(&polygon, [](Polygon *){}), params).request();
    }
}
