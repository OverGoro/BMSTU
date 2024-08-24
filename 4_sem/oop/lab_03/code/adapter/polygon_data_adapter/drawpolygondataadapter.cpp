#include "drawpolygondataadapter.h"
#include "ProjectionAdapterSolution.h"
#include "QDebug"
#include "polygon_adapter/drawpolygonadapter.h"

void DrawPolygonDataAdapter::request() {
    for (auto &polygon : Polygon_data->_polygons)
    {
        DrawPolygonAdapter(std::shared_ptr<Polygon>(&polygon, [](Polygon *){}), drawer, camera).request();
    }
}

