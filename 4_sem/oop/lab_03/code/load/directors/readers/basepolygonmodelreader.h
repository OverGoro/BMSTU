#ifndef BASEPolygonMODELREADER_H
#define BASEPolygonMODELREADER_H

#include "polygon.h"
#include <VectorContainer.h>


class BasePolygonModelReader
{
public:
    BasePolygonModelReader() = default;
    virtual ~BasePolygonModelReader() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual Polygon readPolygon() = 0;
    virtual Vector<Polygon> readPolygons() = 0;
};

#endif // BASEPolygonMODELREADER_H
