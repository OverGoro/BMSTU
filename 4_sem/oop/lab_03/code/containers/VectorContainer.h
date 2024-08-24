#ifndef __VECTORCONTAINER_H__
#define __VECTORCONTAINER_H__

#include "BaseContainer.h"
#include <vector>

template <typename T>
class Vector : BaseContainer
{
public:
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

public:
    Vector() = default;
    ~Vector() = default;
    Vector(const size_type &size, const T &value);
    void push_back(const T &value);
    T pop_back();
    void erase(const iterator &iterator);
    T& operator[](const size_type &index);
    const T& operator[](const size_type &index) const;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    size_type size() const noexcept override;
    void clear();
    bool empty() const;
    void resize(size_type new_size);
    void resize(size_type new_size, const T& value);
    template <typename... Args>
    void emplace_back(Args&&... args);

private:
    std::vector<T> data;
};

#include "VectorContainer.hpp"
#endif // __VECTORCONTAINER_H__
