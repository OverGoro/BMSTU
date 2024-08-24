#include "DrawCarcasModelAdapter.h"
#include "drawcarcasdataadapter.h"


void DrawCarcasModelAdapter::request()
{
    DrawCarcasDataAdapter(std::shared_ptr<CarcasData>(&model->data, [](CarcasData*){}), drawer, camera).request();
}
