#ifndef __SCALECAMERAADAPTER_H__
#define __SCALECAMERAADAPTER_H__
#include "baseperspectivecameraadapter.h"
#include <PerspectiveCamera.h>
#include "../../auxillary_classes/TransformParams.hpp"
class ScalePerspectiveCameraAdapter : public BasePerspectiveCameraAdapter
{
public:
    ScalePerspectiveCameraAdapter() = default;
    ScalePerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &camera, const ScaleParams &params);
    ScalePerspectiveCameraAdapter(const ScalePerspectiveCameraAdapter &camera) = default;
    ScalePerspectiveCameraAdapter &operator=(const ScalePerspectiveCameraAdapter &camera) = default;
    ~ScalePerspectiveCameraAdapter() = default;

    void request();
protected:
    ScaleParams params;
};
#endif // __SCALESCAMERAADAPTER_H__
