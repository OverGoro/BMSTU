#ifndef __SCENE_H__
#define __SCENE_H__

#include "BaseObject.h"
#include "VectorContainer.h"
class Scene
{
    using object_container = Vector<std::shared_ptr<BaseObject>>;
    using iterator = object_container::iterator;
    using iterator_container = Vector<iterator>;
    using size_type = std::size_t;
public:
    Scene() = default;
    ~Scene() = default;
    object_container getObjects() const { return objects; };
    void addObject(std::shared_ptr<BaseObject> object);
    void removeObject(iterator iterator);
    iterator begin();
    iterator end();
    iterator getIterator(const size_type &id);
    iterator getModelIterator(const size_type & id);
    iterator getCameraIterator(const size_type & id);

    iterator_container getCameras() const;

    iterator_container getModels() const;

protected:
    object_container objects;
    iterator_container cameras;
    iterator_container models;
};

#endif // __SCENE_H__
