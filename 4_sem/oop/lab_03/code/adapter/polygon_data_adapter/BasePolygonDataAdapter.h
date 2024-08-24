#ifndef __BASEPolygonDATAADAPTER_H__
#define __BASEPolygonDATAADAPTER_H__

#include "polygon_model/polygondata.h"
#include "BaseAdapter.h"
#include <memory>
class BasePolygonDataAdapter : public BaseAdapter
{
public:
    BasePolygonDataAdapter() = default;
    ~BasePolygonDataAdapter() = default;
protected:
    std::shared_ptr<PolygonData> Polygon_data;
};

#endif // __BASEPolygonDATAADAPTER_H__
