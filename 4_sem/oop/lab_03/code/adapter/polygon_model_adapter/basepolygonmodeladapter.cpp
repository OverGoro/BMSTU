#include "basepolygonmodeladapter.h"

BasePolygonModelAdapter::BasePolygonModelAdapter(const BasePolygonModelAdapter &other)
{
    model = other.model;
}

BasePolygonModelAdapter &BasePolygonModelAdapter::operator=(const BasePolygonModelAdapter &other)
{
    model = other.model;
    return *this;
}
