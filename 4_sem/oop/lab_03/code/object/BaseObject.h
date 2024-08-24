#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include <vector>
#include <memory>
#include "VectorContainer.h"
class BaseObject
{
public:
    using object_container = Vector<std::shared_ptr<BaseObject>>;
    using iterator = object_container::iterator;

public:
    virtual ~BaseObject() = 0;
    virtual bool isComposite() const noexcept = 0;
    virtual bool isVisible() const noexcept = 0;
    virtual iterator begin();
    virtual iterator end();
    virtual void add(std::shared_ptr<BaseObject>);
    virtual void remove(const iterator &it);
};

#endif // __BASEOBJECT_H__
