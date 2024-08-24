#ifndef __VISIBLEOBJECT_H__
#define __VISIBLEOBJECT_H__

#include "BaseObject.h"

class VisibleObject : public BaseObject
{
    bool isVisible() const noexcept override;
    bool isComposite() const noexcept override;

};
#endif // __VISIBLEOBJECT_H__