#include "RotatePolygonModelAdapter.h"//.h"
#include "polygon_data_adapter/RotatePolygonDataAdapter.h"

void RotatePolygonModelAdapter::request()
{
    RotatePolygonDataAdapter(std::shared_ptr<PolygonData>(&this->model->data, [](PolygonData *){}), params).request();
}
