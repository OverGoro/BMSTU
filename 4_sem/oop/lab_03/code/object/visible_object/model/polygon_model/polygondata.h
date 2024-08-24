#ifndef __PolygonDATA_H__
#define __PolygonDATA_H__

#include "VectorContainer.h"
#include "polygon.h"
class PolygonData
{
    friend class CenterPolygonDataAdapter;
    friend class MovePolygonDataAdapter;
    friend class ScalePolygonDataAdapter;
    friend class RotatePolygonDataAdapter;
    friend class DrawPolygonDataAdapter;

    using polygons_type = Vector<Polygon>;
public:
    PolygonData() {};
    PolygonData(const polygons_type &polygons);
    PolygonData(const PolygonData &data);
    PolygonData &operator=(const PolygonData &data);
    PolygonData(PolygonData &&data);
    ~PolygonData() = default;

    void addPolygon(const Polygon &p);
    void addPolygons(const polygons_type &ps);
    
protected:
    polygons_type _polygons;
};

#endif // __PolygonDATA_H__
