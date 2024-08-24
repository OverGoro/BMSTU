#include "polygon_model/polygonmodel.h"

PolygonModel::PolygonModel() { data = PolygonData(); }

PolygonModel::PolygonModel(const PolygonModel &model) : data(model.data){}

PolygonModel &PolygonModel::operator=(const PolygonModel &model)
{
    this->data = model.data;
    return *this;
}

PolygonModel::PolygonModel(const PolygonData &data)
{
    this->data = data;
}
