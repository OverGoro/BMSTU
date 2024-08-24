#include "ScaleCarcasModelAdapter.h"
#include "ScaleCarcasDataAdapter.h"
void ScaleCarcasModelAdapter::request()
{
    ScaleCarcasDataAdapter(std::shared_ptr<CarcasData>(&model->data, [](CarcasData*){}), params).request();
}
