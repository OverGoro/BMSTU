#ifndef __ROTATECAMERAADAPTER_H__
#define __ROTATECAMERAADAPTER_H__
#include "baseperspectivecameraadapter.h"
#include <PerspectiveCamera.h>
#include "../../auxillary_classes/TransformParams.hpp"
class RotatePerspectiveCameraAdapter : public BasePerspectiveCameraAdapter
{
public:
    RotatePerspectiveCameraAdapter() = default;
    RotatePerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &camera, const RotateParams &params);
    RotatePerspectiveCameraAdapter(const RotatePerspectiveCameraAdapter &camera) = default;
    RotatePerspectiveCameraAdapter &operator=(const RotatePerspectiveCameraAdapter &camera) = default;
    ~RotatePerspectiveCameraAdapter() = default;

    void request();
protected:
    RotateParams params;
};
#endif // __ROTATECAMERAADAPTER_H__
