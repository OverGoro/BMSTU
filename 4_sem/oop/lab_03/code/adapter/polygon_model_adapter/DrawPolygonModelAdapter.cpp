#include "DrawPolygonModelAdapter.h"//.h"
#include "polygon_data_adapter/drawpolygondataadapter.h"

void DrawPolygonModelAdapter::request()
{
    DrawPolygonDataAdapter(std::shared_ptr<PolygonData>(&this->model->data, [](PolygonData *){}), drawer, camera).request();
}
