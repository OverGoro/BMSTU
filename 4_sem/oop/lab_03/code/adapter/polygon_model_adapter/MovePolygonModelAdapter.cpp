#include "MovePolygonModelAdapter.h"//.h"
#include "polygon_data_adapter/MovePolygonDataAdapter.h"

void MovePolygonModelAdapter::request()
{
    MovePolygonDataAdapter(std::shared_ptr<PolygonData>(&this->model->data, [](PolygonData *){}), params).request();
}
