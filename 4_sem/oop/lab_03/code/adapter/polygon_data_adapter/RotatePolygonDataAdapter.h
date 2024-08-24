#ifndef __ROTATEPolygonDATAADAPTER_H__
#define __ROTATEPolygonDATAADAPTER_H__


#include "BasePolygonDataAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"

class RotatePolygonDataAdapter : public BasePolygonDataAdapter
{
public:
    RotatePolygonDataAdapter() = default;
    RotatePolygonDataAdapter(std::shared_ptr<PolygonData> data, const RotateParams &params)
        : params(params)
    {
        this->Polygon_data = data;
    };
    ~RotatePolygonDataAdapter() = default;

    void request() override;
protected:
    RotateParams params;

};


#endif // __ROTATEPolygonDATAADAPTER_H__
