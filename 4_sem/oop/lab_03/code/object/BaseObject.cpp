#include "BaseObject.h"
BaseObject::~BaseObject()
{
}
bool BaseObject::isVisible() const noexcept
{
    return false;
}

BaseObject::iterator BaseObject::begin()
{
    return iterator();
}

BaseObject::iterator BaseObject::end()
{
    return iterator();
}

void BaseObject::add(std::shared_ptr<BaseObject>)
{
}

void BaseObject::remove(const iterator &it)
{
}
