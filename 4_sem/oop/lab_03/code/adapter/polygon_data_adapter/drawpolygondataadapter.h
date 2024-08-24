#ifndef __DrawPolygonDATAADAPTER_H__
#define __DrawPolygonDATAADAPTER_H__

#include "BaseCamera.h"
#include "BasePolygonDataAdapter.h"
#include "BaseDrawer.h"
class DrawPolygonDataAdapter : public BasePolygonDataAdapter
{
public:
    DrawPolygonDataAdapter() = default;
    DrawPolygonDataAdapter(const std::shared_ptr<PolygonData> &data,
                           const std::shared_ptr<BaseDrawer> &drawer,
                           const std::shared_ptr<BaseCamera> &camera)
        : drawer(drawer), camera(camera)
    {
        this->Polygon_data = data;
    }
    ~DrawPolygonDataAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseCamera> camera;

};
#endif // __DrawPolygonDATAADAPTER_H__
