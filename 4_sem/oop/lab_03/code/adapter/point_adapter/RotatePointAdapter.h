#ifndef __RotatePOINTADAPTER_H__
#define __RotatePOINTADAPTER_H__

#include "../BasePointAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
class RotatePointAdapter : public BasePointAdapter
{
public:
    RotatePointAdapter() = default;
    ~RotatePointAdapter() = default;
    RotatePointAdapter(std::shared_ptr<Point> point, const RotateParams& params)
        : params(params)
    {
        this->point = point;
    };
    void request() override;
protected:
    RotateParams params;
};

#endif // __RotatePOINTADAPTER_H__