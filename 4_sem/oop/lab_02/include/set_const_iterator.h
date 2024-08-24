#ifndef _CONST_ITERATOR_H
#define _CONST_ITERATOR_H

#include <iterator>
#include "iterator_exception.h"
#include "set_concepts.h"

template <SetType T>
class Set;


template <typename T>
class SetConstIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using node_type = const typename Set<T>::Node;

    using value_type = T;
    using pointer = const std::shared_ptr<value_type>;
    using reference = const value_type &;
    

public:
    SetConstIterator() noexcept = default;
    SetConstIterator(const SetConstIterator<value_type> &it) = default;
    SetConstIterator(const std::shared_ptr<node_type> &node, size_t index = 0);

    bool operator==(const SetConstIterator<value_type> &other) const;
    bool operator!=(const SetConstIterator<value_type> &other) const;

    reference operator*() const;

    pointer operator->() const;

    operator bool() const noexcept;

    SetConstIterator &operator++();
    SetConstIterator operator++(int);

private:
    std::weak_ptr<node_type> value;
    difference_type index;
};

#include "set_const_iterator.hpp"

#endif