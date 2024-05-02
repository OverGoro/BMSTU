#ifndef _CONST_ITERATOR_HPP
#define _CONST_ITERATOR_HPP

// #include "set_const_iterator.h"

template <typename T>
SetConstIterator<T>::SetConstIterator(const std::shared_ptr<typename SetConstIterator<T>::node_type> &node, size_t index)
{
    value = node;
    this->index = index;
}

template <typename T>
bool SetConstIterator<T>::operator==(SetConstIterator<typename SetConstIterator<T>::value_type> const &other) const
{
    return value.lock() == other.value.lock();
}

template <typename T>
inline bool SetConstIterator<T>::operator!=(const SetConstIterator<value_type> &other) const
{
    return value.lock() != other.value.lock();
}

template <typename T>
typename SetConstIterator<T>::reference SetConstIterator<T>::operator*() const
{
    time_t cur_time = time(NULL);
    if (value.expired())
    {
        throw IteratorExpiredPtrException(__FILE__,
                                          typeid(*this).name(),
                                          __LINE__,
                                          ctime(&cur_time));
    }
    return value.lock()->getRef();
}

template <typename T>
typename SetConstIterator<T>::pointer SetConstIterator<T>::operator->() const
{
    return value.lock()->get_pointer;
}

template <typename T>
SetConstIterator<T> &SetConstIterator<T>::operator++()
{   
    // time_t cur_time = time(NULL);
    // if (value.expired())
    // {
    //     throw IteratorExpiredPtrException(__FILE__,
    //                                       typeid(*this).name(),
    //                                       __LINE__,
    //                                       ctime(&cur_time));
    // }
    if (*this)
    {
        value = value.lock()->next;
        index++;
    }
    return *this;
}

template <typename T>
SetConstIterator<T> SetConstIterator<T>::operator++(int)
{
    ++(*this);
    return *this;
}

template <typename T>
SetConstIterator<T>::operator bool() const noexcept
{
    return (value.lock() != nullptr);
}

#endif