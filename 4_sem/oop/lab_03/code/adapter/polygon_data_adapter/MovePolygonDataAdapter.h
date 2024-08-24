#ifndef __MOVEPolygonDATAADAPTER_H__
#define __MOVEPolygonDATAADAPTER_H__

#include "BasePolygonDataAdapter.h"
#include "TransformParams.hpp"
class MovePolygonDataAdapter : public BasePolygonDataAdapter
{
public:
    MovePolygonDataAdapter() = default;
    ~MovePolygonDataAdapter() = default;
    MovePolygonDataAdapter(std::shared_ptr<PolygonData> data, const MoveParams &params)
        : params(params)
    {
        this->Polygon_data = data;
    };

    void request();


protected:
    MoveParams params;
};
#endif // __MOVEPolygonDATAADAPTER_H__
