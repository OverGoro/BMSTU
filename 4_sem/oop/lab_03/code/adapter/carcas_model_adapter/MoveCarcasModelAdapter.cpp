#include "MoveCarcasModelAdapter.h"
#include "MoveCarcasDataAdapter.h"

void MoveCarcasModelAdapter::request()
{
    MoveCarcasDataAdapter(std::shared_ptr<CarcasData>(&model->data, [](CarcasData*){}), params).request();
}
