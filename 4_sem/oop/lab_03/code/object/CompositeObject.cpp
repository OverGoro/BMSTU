#include "CompositeObject.h"

void CompositeObject::add(std::shared_ptr<BaseObject> object)
{
    objects.push_back(object);
}

void CompositeObject::remove(const iterator &iterator)
{
    objects.erase(iterator);
}

CompositeObject::iterator CompositeObject::begin()
{
    return objects.begin();
}

CompositeObject::iterator CompositeObject::end()
{
    return objects.end();
}

bool CompositeObject::isVisible() const noexcept
{
    return false;
}

bool CompositeObject::isComposite() const noexcept
{
    return true;
}
