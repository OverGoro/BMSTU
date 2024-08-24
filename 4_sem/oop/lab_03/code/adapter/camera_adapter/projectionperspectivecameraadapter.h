#ifndef PROJECTIONPerspectiveCAMERAADAPTER_H
#define PROJECTIONPerspectiveCAMERAADAPTER_H

#include "baseperspectivecameraadapter.h"
#include "PerspectiveCamera.h"
class ProjectionPerspectiveCameraAdapter : public BasePerspectiveCameraAdapter
{
public:
    ProjectionPerspectiveCameraAdapter() = default;
    ProjectionPerspectiveCameraAdapter(const std::shared_ptr<PerspectiveCamera> &cam,
                                        const std::shared_ptr<Point>& projected,
                                        const Point &point);
    ~ProjectionPerspectiveCameraAdapter() = default;

    void request();

protected:
    Point point;
    std::shared_ptr<Point> projected;
};

#endif // PROJECTIONPerspectiveCAMERAADAPTER_H
