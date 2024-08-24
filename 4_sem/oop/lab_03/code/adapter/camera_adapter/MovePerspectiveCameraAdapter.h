#ifndef __MOVECAMERAADAPTER_H__
#define __MOVECAMERAADAPTER_H__

#include "baseperspectivecameraadapter.h"
#include "TransformParams.hpp"

class MovePerspectiveCameraAdapter : public BasePerspectiveCameraAdapter
{
public:
    MovePerspectiveCameraAdapter() = default;
    MovePerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &cam, const MoveParams& params);
    ~MovePerspectiveCameraAdapter() = default;

    void request();

protected:
    MoveParams params;
};

#endif // __MOVECAMERAADAPTER_H__
