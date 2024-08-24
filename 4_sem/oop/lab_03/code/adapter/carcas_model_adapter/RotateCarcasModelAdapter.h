#ifndef __ROTATEMODELADAPTER_H__
#define __ROTATEMODELADAPTER_H__

#include "CarcasModel.h"
#include "BaseModelAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
class RotateCarcasModelAdapter : public BaseModelAdapter
{
public:
    RotateCarcasModelAdapter() = default;
    RotateCarcasModelAdapter(const std::shared_ptr<CarcasModel> &model, const RotateParams &params)
        :params(params)
    {
        this->model = model;
    };
    ~RotateCarcasModelAdapter() = default;
    void request();

protected:
    RotateParams params;
    std::shared_ptr<CarcasModel> model;
};

#endif // __ROTATEMODELADAPTER_H__
