#ifndef __DrawCARCASDATAADAPTER_H__
#define __DrawCARCASDATAADAPTER_H__

#include "BaseCamera.h"
#include "BaseCarcasDataAdapter.h"
#include "BaseDrawer.h"
class DrawCarcasDataAdapter : public BaseCarcasDataAdapter
{
public:
    DrawCarcasDataAdapter() = default;
    DrawCarcasDataAdapter(const std::shared_ptr<CarcasData> &data,
                           const std::shared_ptr<BaseDrawer> &drawer,
                           const std::shared_ptr<BaseCamera> &camera)
        : drawer(drawer), camera(camera)
    {
        this->carcas_data = data;
    }
    ~DrawCarcasDataAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseCamera> camera;

};
#endif // __DrawCARCASDATAADAPTER_H__
