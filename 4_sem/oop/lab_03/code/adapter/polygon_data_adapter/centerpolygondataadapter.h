#ifndef CENTERPolygonDATAADAPTER_H
#define CENTERPolygonDATAADAPTER_H

#include "BasePolygonDataAdapter.h"
class CenterPolygonDataAdapter : public BasePolygonDataAdapter
{
public:
    CenterPolygonDataAdapter() = default;
    ~CenterPolygonDataAdapter() = default;
    CenterPolygonDataAdapter(std::shared_ptr<PolygonData> data, const std::shared_ptr<Point> &center)
    {
        this->Polygon_data = data;
        this->center = center;
    };

    void request();


protected:
    std::shared_ptr<Point> center;
};

#endif // CENTERPolygonDATAADAPTER_H
