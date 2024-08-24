#ifndef __MOVEPOLYGONMODELADAPTER_H__
#define __MOVEPOLYGONMODELADAPTER_H__


#include "basepolygonmodeladapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
#include <memory>
class MovePolygonModelAdapter : public BasePolygonModelAdapter
{
public:
    MovePolygonModelAdapter() = default;
    ~MovePolygonModelAdapter() = default;
    MovePolygonModelAdapter(const std::shared_ptr<PolygonModel> &model, const MoveParams &params)
        : params(params)
    {
        this->model = model;
    };

    void request();

protected:
    MoveParams params;
};

#endif // __MOVEMODELADAPTER_H__
