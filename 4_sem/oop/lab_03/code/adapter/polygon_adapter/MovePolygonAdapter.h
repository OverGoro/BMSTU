#ifndef __MOVEPolygonADAPTER_H__
#define __MOVEPolygonADAPTER_H__
#include "../../auxillary_classes/TransformParams.hpp"
#include "basepolygonadapter.h"
#include "polygon.h"
class MovePolygonAdapter : public BasePolygonAdapter
{
public:
    MovePolygonAdapter() = default;
    MovePolygonAdapter(std::shared_ptr<Polygon> polygon, const MoveParams &params)
        : params(params)
    {
        this->polygon = polygon;
    };
    ~MovePolygonAdapter() = default;

    void request() override;
protected:
    MoveParams params;
};

#endif // __MOVEPolygonADAPTER_H__
