#ifndef __BASEPOINTADAPTER_H__
#define __BASEPOINTADAPTER_H__

#include "BaseAdapter.h"
#include "Point.h"
#include <memory>

class BasePointAdapter : public BaseAdapter
{
public:
    BasePointAdapter() = default;
    ~BasePointAdapter() = default;
protected:
    std::shared_ptr<Point> point;
};

#endif // __BASEPOINTADAPTER_H__