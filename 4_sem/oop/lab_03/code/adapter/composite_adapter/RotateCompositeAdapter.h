#ifndef __RotateCOMPOSITEADAPTER_H__
#define __RotateCOMPOSITEADAPTER_H__

#include "BaseCompositeAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
#include "Point.h"
class RotateCompositeAdapter : public BaseCompositeAdapter
{
public:
    RotateCompositeAdapter() = default;
    ~RotateCompositeAdapter() = default;
    RotateCompositeAdapter(const std::shared_ptr<CompositeObject> &model, const RotateParams &params)
        : BaseCompositeAdapter(model), params(params){};
    void request();
protected:
    RotateParams params;
};

#endif // __RotateCOMPOSITEADAPTER_H__