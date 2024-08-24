#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "BaseManager.h"
#include "Scene.h"
#include "BaseCamera.h"
class SceneManager : public BaseManager
{
public:
    SceneManager() = default; 
    SceneManager(const std::shared_ptr<Scene> &scene_) : scene(scene_) {}
    SceneManager(const SceneManager &other) = default;
    SceneManager &operator=(const SceneManager &other) = default;
    SceneManager(SceneManager &&other) = default;
    SceneManager &operator=(SceneManager &&other) = default;
    ~SceneManager() = default;
    std::shared_ptr<Scene> getScene() const { return scene; }
    void setScene(const std::shared_ptr<Scene> &scene_) { scene = scene_; }
    std::shared_ptr<BaseCamera> getCamera() const { return camera; }
    void setCamera(const std::shared_ptr<BaseCamera> &camera_) { camera = camera_; }
protected:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<BaseCamera> camera;
};

#endif // __SCENEMANAGER_H__
