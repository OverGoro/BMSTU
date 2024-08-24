#ifndef __BASEPOLYGONMODELADAPTER_H__
#define __BASEPOLYGONMODELADAPTER_H__
#include <memory>
#include "polygon_model/polygonmodel.h"
#include "BaseAdapter.h"
class BasePolygonModelAdapter : public BaseAdapter
{
public:
    BasePolygonModelAdapter() = default;
    BasePolygonModelAdapter(const std::shared_ptr<PolygonModel> &model);
    BasePolygonModelAdapter(const BasePolygonModelAdapter &other);
    BasePolygonModelAdapter &operator=(const BasePolygonModelAdapter &other);
    ~BasePolygonModelAdapter() = default;

protected:
    std::shared_ptr<PolygonModel> model;
};

#endif // __BASEPOLYGONMODELADAPTER_H__
