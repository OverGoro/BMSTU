#include "centerpolygonmodeladapter.h"
#include "polygon_data_adapter/centerpolygondataadapter.h"
void CenterPolygonModelAdapter::request()
{
    CenterPolygonDataAdapter(std::shared_ptr<PolygonData>(&model->data, [](PolygonData *){}), center).request();
}
