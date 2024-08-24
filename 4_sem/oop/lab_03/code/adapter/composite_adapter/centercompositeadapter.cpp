#include "centercompositeadapter.h"
#include "centeradaptersolution.h"
CenterCompositeAdapter::CenterCompositeAdapter(const std::shared_ptr<CompositeObject> &composite, const std::shared_ptr<Point> &center)
{
    this->center = center;
    this->composite = composite;
}

void CenterCompositeAdapter::request()
{
    for (auto obj_ptr : *composite)
    {
        CenterAdapterSolution().create(obj_ptr, center);
    }
}
