#ifndef __SET_H
#define __SET_H

#include <stdarg.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <ostream>

#include "iterator_concepts.h"
#include "base_set.h"
#include "set_const_iterator.h"
#include "set_concepts.h"
#include "set_exception.h"

template <SetType T>
class Set final : public BaseSet
{
public:
    using iterator = SetConstIterator<T>;
    using const_iterator = SetConstIterator<T>;
    using value_type = T;
    friend const_iterator;

    // Методы.
public:
    // Конструкторы

    Set(); // Инициализации

    explicit Set(const Set<T> &s);
    Set<T> &operator=(const Set<T> &set);

    template <SetType U>
        requires Convertable<T, U>
    explicit Set(const Set<U> &s);
    template <SetType U>
        requires Convertable<T, U>
    Set<T> &operator=(const Set<U> &s);

    Set(Set<T> &&s) noexcept;
    Set<T> &operator=(Set<T> &&set) noexcept;

    template <typename I>
        requires IteratorConcepts::ForwardIterator<I> && std::convertible_to<typename I::value_type, T>
    Set(const I &begin, const I &end); // Конструктор по итератору

    template <typename I>
        requires IteratorConcepts::ForwardIterator<I> && std::convertible_to<typename I::value_type, T>
    Set(const I &begin, const size_type &num); // Конструктор по итератору и количеству

    template <class C>  
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    explicit Set(const C &container); // Конструктор по другому контейнеру
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &operator=(const C &container);

    Set(size_type array_len, const T *array); // Инициализация по массиву

    template <SetType U>
        requires Convertable<T, U>
    Set(size_type array_len, const U *array); // Инициализация по массиву

    Set(std::initializer_list<T> args); // Инициализация по списку данных
    Set<T> &operator=(std::initializer_list<T> args);

    // Деструкторы
    ~Set();

    operator bool() const noexcept; // Пустое множество или нет
    // Операторы
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    bool operator==(const C &container) const; // Сравнение множеств

#pragma region ADD ELEMENT
    void add(const T &element); // Добавить элемент
    template <SetType U>
        requires Convertable<T, U>
    Set<T> operator+(const U &element) const; // Добавление элемента
    template <SetType U>
        requires Convertable<T, U>
    friend Set<T> operator+(const U &element, Set<T> &t); // Добавление элемента
    template <SetType U>
        requires Convertable<T, U>
    Set<T> &operator+=(const U &element); // Добавление эелемнта
#pragma endregion

#pragma region ADD CONTAINER
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    void add(const C &container);

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> operator+(const C &container) const; // Объединение с котнейнером
    // template <class C>
    //     requires Container<C> && ConvertableTo<typename C::value_type, T>
    // friend Set<T> operator+(const C &container, Set<T> &t); // Объединение с контейнером
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &operator+=(const C &container); // Объединение с контейнером
#pragma endregion

#pragma region ADD INTIALIZER LIST
    void add(std::initializer_list<T> args);
    Set<T> &operator+=(std::initializer_list<T> args); // Объединение с списком инициализации
    Set<T> operator+(std::initializer_list<T> args);   // Объединение с списком инициализации
    template <SetType U>
    friend Set<U> operator+(std::initializer_list<U> args, Set<U> &set); // Объединение с списком инициализации
#pragma endregion

#pragma region REMOVE ELEMENT
    void remove(const T &element); // Удалить элемент по значению
    template <SetType U>
        requires Convertable<T, U>
    Set<T> operator-(const U &element) const; // Удалить элемент из множества
    template <SetType U>
        requires Convertable<T, U>
    Set<T> &operator-=(const U &element); // Удалить элемент из множества
#pragma endregion

#pragma region REMOVE CONTAINER
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    void remove(const C &container);

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> operator-(const C &container) const; //  Разность с контейнером
    // template <class C>
    //     requires Container<C> && ConvertableTo<typename C::value_type, T>
    // friend Set<T> operator-(const C &container, Set<T> &t); // Объединение с контейнером
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &operator-=(const C &container); // Разность с контейнером
#pragma endregion

#pragma region REMOVE INIT LIST
    void remove(std::initializer_list<T> args);
    Set<T> &operator-=(std::initializer_list<T> args); // Разность с списком инициализации
    Set<T> operator-(std::initializer_list<T> args);   // Разность с списком инициализации
    // friend Set<T> operator-(std::initializer_list<T> args, Set<T> &set); // Разность с списком инициализации

#pragma endregion

    void clear();
    void update();

#pragma region INTERSECT CONTAINER
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> intersect(const C &container); // Пересечение множеств

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &intersect_update(const C &container); // Записать пересечение

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> operator&(const C &container) const; //
    // template <class C>
    //     requires Container<C> && ConvertableTo<typename C::value_type, T>
    // friend Set<T> operator&(const C &container, Set<T> &t); // Объединение с контейнером
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &operator&=(const C &container); // Разность с контейнером
#pragma endregion

#pragma region INTERSECT INITIALIZER LIST
    Set<T> intersect(std::initializer_list<T> args); // Пересечение множеств

    Set<T> &intersect_update(std::initializer_list<T> args); // Записать пересечение

    Set<T> &operator&=(std::initializer_list<T> args); //
    Set<T> operator&(std::initializer_list<T> args);   //
    // friend Set<T> operator&(std::initializer_list<T> args, Set<T> &set); //
#pragma endregion

#pragma region UNITE CONTAINETR
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> unite(const C &container); // Объединение множеств

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &unite_update(const C &container); // Записать объединение
#pragma endregion

#pragma region UNITE INIT LIST
    Set<T> unite(std::initializer_list<T> args); // Объединение множеств

    Set<T> &unite_update(std::initializer_list<T> args); // Записать объединение
#pragma endregion

#pragma region DIFFERENCE CONTAINER
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> difference(const C &container); // разнсоть множеств

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &difference_update(const C &container); // Записать разность
#pragma endregion

#pragma region DIFFERENCE INITIALIZER LIST
    Set<T> difference(std::initializer_list<T> args); // разнсоть множеств

    Set<T> &difference_update(std::initializer_list<T> args); // Записать разность
#pragma endregion

#pragma region SYMMETRIC DIFFERENCE CONTAINER
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> symmetric_difference(const C &container); // симметрическая разнсоть множеств

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &symmetric_difference_update(const C &container); // Записать симметрическую разность

    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> operator^(const C &container) const; //  Разность с контейнером
    // template <class C>
    //     requires Container<C> && ConvertableTo<typename C::value_type, T>
    // friend Set<T> operator^(const C &container, Set<T> &t); // Объединение с контейнером
    template <class C>
        requires Container<C> && ConvertableTo<typename C::value_type, T>
    Set<T> &operator^=(const C &container); // Разность с контейнером
#pragma endregion

#pragma region SYMMETRIC DIFFERENCE INITIALIZER LIST
    Set<T> symmetric_difference(std::initializer_list<T> args); // симметрическая разнсоть множеств

    Set<T> &symmetric_difference_update(std::initializer_list<T> args); // Записать симметрическую разность

    Set<T> &operator^=(std::initializer_list<T> args); // Разность с списком инициализации
    Set<T> operator^(std::initializer_list<T> args);   // Разность с списком инициализации
    // friend Set<T> operator^(std::initializer_list<T> args, Set<T> &set); // Разность с списком инициализации
#pragma endregion

    // Работа с парметрами
    virtual size_type power() const noexcept override;
    virtual size_type size() const noexcept override;
    virtual bool isEmpty() const noexcept override;

    // Итераторы
    const_iterator begin() const;
    const_iterator end() const;

    // Методы
    template <SetType U>
        requires ComparableEquality<T, U>
    bool has(U value) const;

protected:
    class Node
    {
        friend Set<T>::iterator;
        friend Set<T>::const_iterator;

    public:
        Node();
        explicit Node(const T &value);
        explicit Node(const Node &node);
        explicit Node(Node &&node);
        explicit Node(std::shared_ptr<Node> &node);

        std::weak_ptr<Node> get_next();

        void setValue(const T &value);
        void setNext(std::shared_ptr<Node> &node);

        void setNextNull();

        T &getRef();
        const T &getRef() const;
        const T &getValue() const;

        bool operator==(const Node &node) const;
        bool operator!=(const Node &node) const;

        bool operator==(const std::shared_ptr<Node> &node) const;
        bool operator!=(const std::shared_ptr<Node> &node) const;

        ~Node() = default;

    private:
        T value;
        std::shared_ptr<Node> next;
    };
    // Поля
private:
    std::shared_ptr<Node> head; // Значения
};

template <SetType T>
std::ostream &operator<<(std::ostream &os, const Set<T> &set); // Вывод

#include "set_node.hpp"
#include "set.hpp"
#endif
