#ifndef __RotatePOLYGONMODELADAPTER_H__
#define __RotatePOLYGONMODELADAPTER_H__


#include "basepolygonmodeladapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
#include <memory>
class RotatePolygonModelAdapter : public BasePolygonModelAdapter
{
public:
    RotatePolygonModelAdapter() = default;
    ~RotatePolygonModelAdapter() = default;
    RotatePolygonModelAdapter(const std::shared_ptr<PolygonModel> &model, const RotateParams &params)
        : params(params)
    {
        this->model = model;
    };

    void request();

protected:
    RotateParams params;
};

#endif // __RotateMODELADAPTER_H__
