#ifndef __ScalePOINTADAPTER_H__
#define __ScalePOINTADAPTER_H__

#include "../BasePointAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
class ScalePointAdapter : public BasePointAdapter
{
public:
    ScalePointAdapter() = default;
    ScalePointAdapter(std::shared_ptr<Point> point, const ScaleParams &params)
        : params(params)
    {
        this->point = point;
    };
    ~ScalePointAdapter() = default;

    void request() override;
protected:
    ScaleParams params;
};

#endif // __ScalePOINTADAPTER_H__