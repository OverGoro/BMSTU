#ifndef __DRAWCOMPOSITEADAPTER_H__
#define __DRAWCOMPOSITEADAPTER_H__

#include "BaseCompositeAdapter.h"
#include "BaseDrawer.h"
#include "BaseCamera.h"
#include "CompositeObject.h"
class DrawCompositeAdapter : public BaseCompositeAdapter
{
public:
    DrawCompositeAdapter() = default;
    DrawCompositeAdapter(const std::shared_ptr<CompositeObject> &composite, 
                        const std::shared_ptr<BaseDrawer> &drawer,
                        const std::shared_ptr<BaseCamera> &camera)
        : drawer(drawer), camera(camera)
    {
        this->composite = composite;
    }
    ~DrawCompositeAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseCamera> camera;
};

#endif // __DRAWCOMPOSITEADAPTER_H__