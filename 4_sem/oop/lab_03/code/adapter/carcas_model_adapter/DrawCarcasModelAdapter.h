#ifndef __DRAWMODELADAPTER_H__
#define __DRAWMODELADAPTER_H__

#include "BaseModelAdapter.h"
#include "BaseDrawer.h"
#include "CarcasModel.h"
#include "BaseCamera.h"
class DrawCarcasModelAdapter : public BaseModelAdapter
{
public:
    DrawCarcasModelAdapter() = default;
    DrawCarcasModelAdapter(const std::shared_ptr<CarcasModel> &model,
                           const std::shared_ptr<BaseDrawer> &drawer,
                           const std::shared_ptr<BaseCamera> &camera)
        : drawer(drawer), camera(camera)
    {
        this->model = model;
    }
    ~DrawCarcasModelAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<CarcasModel> model;
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseCamera> camera;
};

#endif // __DRAWMODELADAPTER_H__
