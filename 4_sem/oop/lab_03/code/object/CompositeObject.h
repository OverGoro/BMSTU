#ifndef __COMPOSITEOBJECT_H__
#define __COMPOSITEOBJECT_H__

#include "VectorContainer.h"
#include "BaseObject.h"

class CompositeObject : public BaseObject
{
public:
    CompositeObject() = default;
    ~CompositeObject() = default;
    void add(std::shared_ptr<BaseObject>) override;
    void remove(const iterator &it) override;
    iterator begin() override;
    iterator end() override;
    bool isVisible() const noexcept override;
    bool isComposite() const noexcept override;

protected:
    object_container objects;
};

#endif // __COMPOSITEOBJECT_H__
