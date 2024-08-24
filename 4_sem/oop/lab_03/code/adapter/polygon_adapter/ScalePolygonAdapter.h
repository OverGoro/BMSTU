#ifndef __ScalePolygonADAPTER_H__
#define __ScalePolygonADAPTER_H__

#include "basepolygonadapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
class ScalePolygonAdapter : public BasePolygonAdapter
{
public:
    ScalePolygonAdapter() = default;
    ScalePolygonAdapter(std::shared_ptr<Polygon> polygon, const ScaleParams &params)
        : params(params)
    {
        this->polygon = polygon;
    };
    ~ScalePolygonAdapter() = default;

    void request() override;
protected:
    ScaleParams params;
};

#endif // __ScalePolygonADAPTER_H__
