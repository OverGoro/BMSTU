#include "RotateCarcasModelAdapter.h"
#include "RotateCarcasDataAdapter.h"
void RotateCarcasModelAdapter::request()
{
    RotateCarcasDataAdapter(std::shared_ptr<CarcasData>(&model->data, [](CarcasData*){}), params).request();
}
