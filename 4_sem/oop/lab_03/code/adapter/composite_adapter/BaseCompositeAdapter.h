#ifndef __BASECOMPOSITEADAPTER_H__
#define __BASECOMPOSITEADAPTER_H__

#include "BaseAdapter.h"
#include "CompositeObject.h"
class BaseCompositeAdapter : public BaseAdapter
{
public:
    BaseCompositeAdapter() = default;
    BaseCompositeAdapter(const std::shared_ptr<CompositeObject> &composite)
        : composite(composite){}
    ~BaseCompositeAdapter() = default;
protected:
    std::shared_ptr<CompositeObject> composite;
};
#endif // __BASECOMPOSITEADAPTER_H__
