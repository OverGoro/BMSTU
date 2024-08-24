#ifndef CENTERCARCASMODELADAPTER_H
#define CENTERCARCASMODELADAPTER_H

#include "BaseCamera.h"
#include "BaseModelAdapter.h"
#include "CarcasModel.h"

class CenterCarcasModelAdapter : public BaseModelAdapter
{
public:
    CenterCarcasModelAdapter() = default;
    CenterCarcasModelAdapter(const std::shared_ptr<CarcasModel> &model,
                           const std::shared_ptr<Point> &center)
    {
        this->model = model;
        this->center = center;
    }
    ~CenterCarcasModelAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<Point> center;
    std::shared_ptr<CarcasModel> model;
};

#endif // CENTERCARCASMODELADAPTER_H
