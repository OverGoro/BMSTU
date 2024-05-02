#ifndef __SET_NODE_H__
#define __SET_NODE_H__

#include "set.h"

template <SetType T>
Set<T>::Node::Node(const T &value)
{
    this->value = value;
    this->next = nullptr;
}

template <SetType T>
Set<T>::Node::Node(const Node &node)
{
    this->value = node.value;
    this->next = node.next;
}

template <SetType T>
Set<T>::Node::Node(Node &&node)
{
    this->value = node.value;
    this->next = node.next;
}

template <SetType T>
Set<T>::Node::Node(std::shared_ptr<Node> &node)
{
    this->value = (*node)->value;
    this->next = (*node)->next;
}

template <SetType T>
std::weak_ptr<typename Set<T>::Node> Set<T>::Node::get_next()
{
    return next;
}

template <SetType T>
void Set<T>::Node::setValue(const T &value)
{
    this->value = value;
}

template <SetType T>
void Set<T>::Node::setNext(std::shared_ptr<Node> &node)
{
    next = node;
}

template <SetType T>
void Set<T>::Node::setNextNull()
{
    next.reset();
}

template <SetType T>
T &Set<T>::Node::getRef()
{
    return value;
}

template <SetType T>
const T &Set<T>::Node::getRef() const
{
    return value;
}

template <SetType T>
const T &Set<T>::Node::getValue() const
{
    return value;
}

template <SetType T>
bool Set<T>::Node::operator==(const Node &node) const
{
    return (value == node.value && next == node.next);
}

template <SetType T>
bool Set<T>::Node::operator!=(const Node &node) const
{
    return !(*this == node);
}

template <SetType T>
bool Set<T>::Node::operator==(const std::shared_ptr<Node> &node) const
{
    return (*this == (*node));
}

template <SetType T>
bool Set<T>::Node::operator!=(const std::shared_ptr<Node> &node) const
{
    return (*this != (*node));
}

#endif // __SET_NODE_H__