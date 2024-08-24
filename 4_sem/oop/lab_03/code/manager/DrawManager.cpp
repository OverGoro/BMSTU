#include "DrawManager.h"
#include "DrawAdapterSolution.h"  
#include "Exceptions.h"
void DrawManager::drawScene(std::shared_ptr<Scene> scene, std::shared_ptr<BaseDrawer> drawer)
{
    if (camera == nullptr)
        throw CameraNotSetException();
    for (auto obj : *scene)
    {
        if (obj->isVisible())
        {
            auto adapter = DrawAdapterSolution().create(obj, drawer, camera);
            adapter->request();
        }
    }
}

void DrawManager::clearScene(std::shared_ptr<BaseDrawer> drawer)
{
    drawer->clear();
    drawer->clearZBuffer();
}
