#include "polygondata.h"

PolygonData::PolygonData(const polygons_type &polygons)
{
    _polygons = polygons;
}

PolygonData::PolygonData(const PolygonData &data)
{
    _polygons = data._polygons;
}

PolygonData &PolygonData::operator=(const PolygonData &data)
{
    _polygons = data._polygons;
    return *this;
}

PolygonData::PolygonData(PolygonData &&data)
{
    _polygons = data._polygons;
}

void PolygonData::addPolygon(const Polygon &p)
{
    _polygons.push_back(p);
}

void PolygonData::addPolygons(const polygons_type &ps)
{
    for (const auto &p : ps)
    {
        addPolygon(p);
    }
}
