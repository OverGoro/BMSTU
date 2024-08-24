#ifndef __MOVEPOINTADAPTER_H__
#define __MOVEPOINTADAPTER_H__
#include "../../auxillary_classes/TransformParams.hpp"
#include "../BasePointAdapter.h"
class MovePointAdapter : public BasePointAdapter
{
public:
    MovePointAdapter() = default;
    MovePointAdapter(std::shared_ptr<Point> point, const MoveParams &params)
        : params(params)
    {
        this->point = point;
    };
    ~MovePointAdapter() = default;

    void request() override;
protected:
    MoveParams params;
};

#endif // __MOVEPOINTADAPTER_H__