#ifndef __BASECONTAINER_H__
#define __BASECONTAINER_H__

#include <cstddef>

class BaseContainer
{
public:
    using size_type = std::size_t;
protected:
    BaseContainer() = default;
    ~BaseContainer() = default;
public:
    virtual size_type size() const noexcept { return len; };
protected:
    size_type len;
};

#endif // __BASECONTAINER_H__