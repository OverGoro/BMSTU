#ifndef __SCALEPolygonDATAADAPTER_H__
#define __SCALEPolygonDATAADAPTER_H__
#include "BasePolygonDataAdapter.h"
#include "../../auxillary_classes/TransformParams.hpp"
class ScalePolygonDataAdapter : public BasePolygonDataAdapter
{
public:
    ScalePolygonDataAdapter() = default;
    ScalePolygonDataAdapter(std::shared_ptr<PolygonData> data, const ScaleParams& params )
        : params(params)
    {
        Polygon_data = data;
    };
    ~ScalePolygonDataAdapter() = default;

    void request() override;
protected:
    ScaleParams params;
};

#endif // __SCALEPolygonDATAADAPTER_H__
