#ifndef __RotatePolygonADAPTER_H__
#define __RotatePolygonADAPTER_H__

#include "basepolygonadapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
class RotatePolygonAdapter : public BasePolygonAdapter
{
public:
    RotatePolygonAdapter() = default;
    ~RotatePolygonAdapter() = default;
    RotatePolygonAdapter(std::shared_ptr<Polygon> polygon, const RotateParams& params)
        : params(params)
    {
        this->polygon = polygon;
    };
    void request() override;
protected:
    RotateParams params;
};

#endif // __RotatePolygonADAPTER_H__
