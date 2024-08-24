#ifndef __ScalePOLYGONMODELADAPTER_H__
#define __ScalePOLYGONMODELADAPTER_H__


#include "basepolygonmodeladapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
#include <memory>
class ScalePolygonModelAdapter : public BasePolygonModelAdapter
{
public:
    ScalePolygonModelAdapter() = default;
    ~ScalePolygonModelAdapter() = default;
    ScalePolygonModelAdapter(const std::shared_ptr<PolygonModel> &model, const ScaleParams &params)
        : params(params)
    {
        this->model = model;
    };

    void request();

protected:
    ScaleParams params;
};

#endif // __ScaleMODELADAPTER_H__
