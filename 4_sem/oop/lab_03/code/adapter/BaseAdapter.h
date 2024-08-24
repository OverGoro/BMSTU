#ifndef __BASEADAPTER_H__
#define __BASEADAPTER_H__

class BaseAdapter
{
public:
    BaseAdapter() = default;
    virtual ~BaseAdapter() = default;
    virtual void request() = 0;
};

#endif // __BASEADAPTER_H__