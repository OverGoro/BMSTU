#ifndef CENTERPerspectiveCAMERAADAPTER_H
#define CENTERPerspectiveCAMERAADAPTER_H

#include "baseperspectivecameraadapter.h"//.h"
#include "PerspectiveCamera.h"
class CenterPerspectiveCameraAdapter : public BasePerspectiveCameraAdapter
{
public:
    CenterPerspectiveCameraAdapter() = default;
    CenterPerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &cam, const std::shared_ptr<Point>& center);
    ~CenterPerspectiveCameraAdapter() = default;

    void request();

protected:
    std::shared_ptr<Point> center;
};

#endif // CENTERPerspectiveCAMERAADAPTER_H
