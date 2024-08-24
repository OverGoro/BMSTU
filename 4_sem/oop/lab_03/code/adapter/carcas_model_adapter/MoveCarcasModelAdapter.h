#ifndef __MOVEMODELADAPTER_H__
#define __MOVEMODELADAPTER_H__


#include "BaseModelAdapter.h"
#include "CarcasModel.h"
#include "../../auxillary_classes/TransformParams.hpp"
#include <memory>
class MoveCarcasModelAdapter : public BaseModelAdapter
{
public:
    MoveCarcasModelAdapter() = default;
    ~MoveCarcasModelAdapter() = default;
    MoveCarcasModelAdapter(const std::shared_ptr<CarcasModel> &model, const MoveParams &params)
        : params(params)
    {
        this->model = model;
    };

    void request();

protected:
    MoveParams params;
    std::shared_ptr<CarcasModel> model;
};

#endif // __MOVEMODELADAPTER_H__
