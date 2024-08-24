#ifndef __MOVECOMPOSITEADAPTER_H__
#define __MOVECOMPOSITEADAPTER_H__

#include "BaseCompositeAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"

class MoveCompositeAdapter : public BaseCompositeAdapter
{
public:
    MoveCompositeAdapter() = default;
    ~MoveCompositeAdapter() = default;
    MoveCompositeAdapter(const std::shared_ptr<CompositeObject> &model, const MoveParams &params)
        : BaseCompositeAdapter(model), params(params){};

    void request();

protected:
    MoveParams params;
};

#endif // __MOVECOMPOSITEADAPTER_H__