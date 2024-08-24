#include "Scene.h"
#include "BaseCamera.h"
#include "BaseModel.h"
void Scene::addObject(std::shared_ptr<BaseObject> object)
{
    objects.push_back(object);
    cameras.clear();
    models.clear();
    for (auto it = objects.begin(); it < objects.end(); it++)
    {
        if (dynamic_pointer_cast<BaseCamera>(*it))
            cameras.push_back(it);
        else if (dynamic_pointer_cast<BaseModel>(*it))
            models.push_back(it);
    }
}

void Scene::removeObject(iterator iterator)
{
    for (auto it = cameras.begin(); it < cameras.end(); it++)
    {
        if (*it == iterator)
            cameras.erase(it);
    }
    for (auto it = models.begin(); it < models.end(); it++)
    {
        if (*it == iterator)
            models.erase(it);
    }
    objects.erase(iterator);
}

Scene::iterator Scene::begin()
{
    return objects.begin();
}

Scene::iterator Scene::end()
{
    return objects.end();
}

Scene::iterator Scene::getIterator(const Scene::size_type &id)
{
    iterator it = objects.begin();
    for (Scene::size_type i = 0; i < id; i++)
    {
        it++;
    }
    return it;
}

Scene::iterator Scene::getModelIterator(const size_type &id)
{
    auto it = models.begin();
    for (Scene::size_type i = 0; i < id; i++)
    {
        it++;
    }
    return *it;
}

Scene::iterator Scene::getCameraIterator(const size_type &id)
{
    auto it = cameras.begin();
    for (Scene::size_type i = 0; i < id; i++)
    {
        it++;
    }
    return *it;
}

Scene::iterator_container Scene::getCameras() const { return cameras; }

Scene::iterator_container Scene::getModels() const { return models; }
