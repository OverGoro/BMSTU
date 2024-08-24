#ifndef BASEPerspectiveCAMERAADAPTER_H
#define BASEPerspectiveCAMERAADAPTER_H

#include "BaseCameraAdapter.h"
#include "PerspectiveCamera.h"
class BasePerspectiveCameraAdapter : public BaseCameraAdapter
{
public:
    BasePerspectiveCameraAdapter() = default;
    ~BasePerspectiveCameraAdapter() = default;
protected:
    std::shared_ptr<PerspectiveCamera> camera;
};
#endif // BASEPerspectiveCAMERAADAPTER_H
