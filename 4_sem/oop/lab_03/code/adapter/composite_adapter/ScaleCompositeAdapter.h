#ifndef __ScaleCOMPOSITEADAPTER_H__
#define __ScaleCOMPOSITEADAPTER_H__

#include "BaseCompositeAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
#include "Point.h"
class ScaleCompositeAdapter : public BaseCompositeAdapter
{
public:
    ScaleCompositeAdapter() = default;
    ~ScaleCompositeAdapter() = default;
    ScaleCompositeAdapter(const std::shared_ptr<CompositeObject> &model, const ScaleParams &params)
        : BaseCompositeAdapter(model), params(params){};

    void request();

protected:
    ScaleParams params;
};

#endif // __ScaleCOMPOSITEADAPTER_H__