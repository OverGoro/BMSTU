#ifndef _BASE_SET_HPP
#define _BASE_SET_HPP

#include <stddef.h>

class BaseSet
{
public:
    using size_type = size_t;

protected:
    BaseSet() = default;
    ~BaseSet() = default;
public:
    virtual size_type size() const noexcept = 0;
    virtual size_type power() const noexcept = 0;
    virtual bool isEmpty() const noexcept = 0;

protected:
    size_type len;
};
#endif
