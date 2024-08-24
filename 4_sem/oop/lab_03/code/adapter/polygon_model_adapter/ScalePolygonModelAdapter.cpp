#include "ScalePolygonModelAdapter.h"//.h"
#include "polygon_data_adapter/ScalePolygonDataAdapter.h"

void ScalePolygonModelAdapter::request()
{
    ScalePolygonDataAdapter(std::shared_ptr<PolygonData>(&this->model->data, [](PolygonData *){}), params).request();
}
