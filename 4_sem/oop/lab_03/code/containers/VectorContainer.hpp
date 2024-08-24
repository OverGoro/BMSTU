#include "VectorContainer.h"
template <typename T>
void Vector<T>::push_back(const T &value)
{
    data.push_back(value);
}

template <typename T>
Vector<T>::Vector(const size_type &size, const T &value)
{
    data = std::vector<T>(size, value);
}


template <typename T>
T Vector<T>::pop_back()
{
    return data.back();
}

template <typename T>
void Vector<T>::erase(const iterator &iterator)
{
    data.erase(iterator);
}

template <typename T>
T &Vector<T>::operator[](const size_type &index)
{
    return data[index];
}

template <typename T>
const T &Vector<T>::operator[](const size_type &index) const
{
    return data[index];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return data.begin();
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return data.end();
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
    return data.begin();
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
    return data.end();
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept
{
    return data.size();
}
template <typename T>
void Vector<T>::clear()
{
    return data.clear();
}
template <typename T>
bool Vector<T>::empty() const
{
    return data.empty();
}

template <typename T>
void Vector<T>::resize(size_type new_size) {
    data.resize(new_size);
}

template <typename T>
void Vector<T>::resize(size_type new_size, const T& value) {
    data.resize(new_size, value);
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args&&... args) {
    data.emplace_back(std::forward<Args>(args)...);
}

