#ifndef __DRAWMANAGER_H__
#define __DRAWMANAGER_H__

#include <memory>
#include "BaseDrawer.h"
#include "Scene.h"
#include "PerspectiveCamera.h"
class DrawManager
{
public:
    DrawManager()
        :camera(nullptr){};
    ~DrawManager() = default;
    void drawScene(std::shared_ptr<Scene> scene, std::shared_ptr<BaseDrawer> drawer);
    void clearScene(std::shared_ptr<BaseDrawer> drawer);
    std::shared_ptr<BaseCamera> getCamera() const { return camera; }
    void setCamera(const std::shared_ptr<BaseCamera> &camera_) { camera = camera_; }
protected:
    std::shared_ptr<BaseCamera> camera;
};

#endif // __DRAWMANAGER_H__