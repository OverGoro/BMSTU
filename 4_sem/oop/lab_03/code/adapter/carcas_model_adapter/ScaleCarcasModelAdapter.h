#ifndef __SCALEMODELADAPTER_H__
#define __SCALEMODELADAPTER_H__

#include "CarcasModel.h"
#include "BaseModelAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
#include <memory>

class ScaleCarcasModelAdapter : public BaseModelAdapter
{
public:
    ScaleCarcasModelAdapter() = default;
    ScaleCarcasModelAdapter(const std::shared_ptr<CarcasModel> &model, const ScaleParams &params)
        :params(params)
    {
        this->model=  model;
    };
    ~ScaleCarcasModelAdapter() = default;
    void request();

protected:
    ScaleParams params;
    std::shared_ptr<CarcasModel> model;
};

#endif // __SCALEMODELADAPTER_H__
