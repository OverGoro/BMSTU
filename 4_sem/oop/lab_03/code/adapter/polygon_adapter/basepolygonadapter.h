#ifndef __BASEPolygonADAPTER_H__
#define __BASEPolygonADAPTER_H__

#include "BaseAdapter.h"
#include "polygon.h"
#include <memory>

class BasePolygonAdapter : public BaseAdapter
{
public:
    BasePolygonAdapter() = default;
    ~BasePolygonAdapter() = default;
protected:
    std::shared_ptr<Polygon> polygon;
};

#endif // __BASEPolygonADAPTER_H__
