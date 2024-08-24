#include "centercarcasmodeladapter.h"
#include "centercarcasdataadapter.h"
#include "CarcasModel.h"
void CenterCarcasModelAdapter::request()
{
    CenterCarcasDataAdapter(std::shared_ptr<CarcasData>(&model->data, [](CarcasData *){}), center).request();
}
