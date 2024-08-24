#ifndef __DrawPolygonADAPTER_H__
#define __DrawPolygonADAPTER_H__
#include "basepolygonadapter.h"
#include "polygon.h"
#include "BaseCamera.h"
#include "BaseDrawer.h"
class DrawPolygonAdapter : public BasePolygonAdapter
{
public:
    DrawPolygonAdapter() = default;
    DrawPolygonAdapter(const std::shared_ptr<Polygon> &data,
                          const std::shared_ptr<BaseDrawer> &drawer,
                          const std::shared_ptr<BaseCamera> &camera)
        : drawer(drawer), camera(camera)
    {
        this->polygon = data;
    }
    ~DrawPolygonAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseCamera> camera;

};

#endif // __DrawPolygonADAPTER_H__
