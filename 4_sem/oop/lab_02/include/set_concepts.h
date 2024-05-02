#ifndef __SET_CONCEPTS_H
#define __SET_CONCEPTS_H
#include <concepts>


template <typename From, typename To>
concept ConvertableTo = std::convertible_to<From, To>;

template <typename To, typename From>
concept ConvertableFrom = std::convertible_to<From, To>;

template <typename T, typename U>
concept Convertable = ConvertableTo<T, U> && ConvertableFrom<T, U>;

template <typename T, typename U>
concept Summable = requires(T a, U b) {
    { a + b } -> std::convertible_to<T>;
    { a += b } -> std::convertible_to<T &>;
};

template <typename T, typename U>
concept Substractable = requires(T a, U b) {
    { a - b } -> std::convertible_to<T>;
    { a -= b } -> std::convertible_to<T &>;
};

template <typename T, typename U>
concept Multable = requires(T a, U b) {
    { a *b } -> std::convertible_to<T>;
    { a *= b } -> std::convertible_to<T &>;
};

template <typename T, typename U>
concept Divable = requires(T a, U b) {
    { a / b } -> std::convertible_to<T>;
    { a /= b } -> std::convertible_to<T &>;
    { b == T(0) } -> std::same_as<bool>;
};

template <typename T>
concept Incrementable = requires(T t) {
    { t++ } -> std::same_as<T>;
    { ++t } -> std::same_as<T&>;
};

template <typename T, typename U>
concept ComparableEquality = requires(T a, U b) {
    { a == b } -> std::same_as<bool>;
    { a != b } -> std::same_as<bool>;
    { b == a } -> std::same_as<bool>;
    { b != a } -> std::same_as<bool>;
};

template <typename T, typename U>
concept ComparableLess = requires(T a, U b) {
    { a < b } -> std::same_as<bool>;
    { b < a } -> std::same_as<bool>;
};

template <typename T, typename U>
concept ComparableGreater = requires(T a, U b) {
    { a > b } -> std::same_as<bool>;
    { b > a } -> std::same_as<bool>;
};

template <class C>
concept Container = requires(C c) {
    typename C::value_type;
    typename C::size_type;
    typename C::iterator;
    typename C::const_iterator;
    { c.begin() } -> std::convertible_to<typename C::iterator>;
    { c.end() } -> std::convertible_to<typename C::iterator>;
    { c.size() } -> std::convertible_to<typename C::size_type>;
};

template <typename T>
concept SetType = ComparableEquality<T, T> && requires(T t, T t2){
    {t = t2} -> std::same_as<T&>;
    //{t = std::move(t2)}; 
};
#endif