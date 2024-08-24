#ifndef __INVISIBLEOBJECT_H__
#define __INVISIBLEOBJECT_H__

#include "BaseObject.h"

class InvisibleObject : public BaseObject
{
public:
    InvisibleObject() = default;
    ~InvisibleObject() = default;
    bool isVisible() const noexcept override;
    bool isComposite() const noexcept override;
};
#endif // __INVISIBLEOBJECT_H__