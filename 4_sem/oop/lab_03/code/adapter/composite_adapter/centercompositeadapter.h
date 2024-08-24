#ifndef CENTERCOMPOSITEADAPTER_H
#define CENTERCOMPOSITEADAPTER_H

#include "BaseCompositeAdapter.h"
#include "Point.h"
class CenterCompositeAdapter : public BaseCompositeAdapter
{
public:
    CenterCompositeAdapter() = default;
    CenterCompositeAdapter(const std::shared_ptr<CompositeObject> &composite,
                           const std::shared_ptr<Point> &center);
    ~CenterCompositeAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<Point> center;
};

#endif // CENTERCOMPOSITEADAPTER_H
