#ifndef __DRAWPOLYGONMODELADAPTER_H__
#define __DRAWPOLYGONMODELADAPTER_H__

#include "basepolygonmodeladapter.h"
#include "BaseDrawer.h"
#include "BaseCamera.h"
#include "polygon_model/polygonmodel.h"
class DrawPolygonModelAdapter : public BasePolygonModelAdapter
{
public:
    DrawPolygonModelAdapter() = default;
    DrawPolygonModelAdapter(const std::shared_ptr<PolygonModel> &model,
                           const std::shared_ptr<BaseDrawer> &drawer,
                           const std::shared_ptr<BaseCamera> &camera)
        : drawer(drawer), camera(camera)
    {
        this->model = model;
    }
    ~DrawPolygonModelAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseCamera> camera;
};

#endif // __DRAWMODELADAPTER_H__
