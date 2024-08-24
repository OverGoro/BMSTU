#ifndef __BASEMODEL_H__
#define __BASEMODEL_H__

#include "VisibleObject.h"

class BaseModel : public VisibleObject
{
public:
    bool isComposite() const noexcept;
};

#endif // __BASEMODEL_H__
