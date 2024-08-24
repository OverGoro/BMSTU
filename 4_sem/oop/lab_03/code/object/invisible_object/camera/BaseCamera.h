#ifndef __BASECAMERA_H__
#define __BASECAMERA_H__

#include "InvisibleObject.h"
#include "Point.h"
#include "../../../auxillary_classes/TransformParams.hpp"    
class BaseCamera : public InvisibleObject
{
public:
    BaseCamera() = default;
    ~BaseCamera() = default;
    // virtual Point getProjection(const Point &) const = 0;
};

#endif // __BASECAMERA_H__
