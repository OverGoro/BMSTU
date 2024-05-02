#ifndef __ITERATOR_CONCEPTS_H__
#define __ITERATOR_CONCEPTS_H__

#include <concepts>
#include <iterator>

namespace IteratorConcepts
{
    template <typename I>
    concept Iterator = requires() {
        typename I::value_type;
        typename I::difference_type;
        typename I::pointer;
        typename I::reference;
    };

    template <typename T, typename U>
    concept DerivedFrom = std::is_base_of<U, T>::value;

#pragma region Input_Iterator
    template <typename T>
    concept EqualityComparable = requires(T a, T b) {
        { a == b } -> std::same_as<bool>;
        { a != b } -> std::same_as<bool>;
    };

    template <typename I>
    concept InputIterator = Iterator<I> &&
                            requires { typename I::iterator_category; } &&
                            EqualityComparable<I> &&
                            DerivedFrom<typename I::iterator_category, std::input_iterator_tag>;

#pragma endregion

#pragma region Forward_Iterator
    template <typename I>
    concept Incrementable = requires(I it) {
        { ++it } -> std::same_as<I &>;
        { it++ } -> std::same_as<I>;
    };

    template <typename I>
    concept ForwardIterator = InputIterator<I> &&
                              Incrementable<I> &&
                              DerivedFrom<typename I::iterator_category, std::forward_iterator_tag>;

#pragma endregion

#pragma region Bidirectional_Iterator
    template <typename I>
    concept Decrementable = requires(I it) {
        { --it } -> std::same_as<I &>;
        { it-- } -> std::same_as<I>;
    };

    template <typename I>
    concept BidirectionalIterator = ForwardIterator<I> &&
                                    Decrementable<I> &&
                                    DerivedFrom<typename I::iterator_category, std::bidirectional_iterator_tag>;

#pragma endregion

#pragma region Random_Access_Iterator
    template <typename I>
    concept RandomAccess = requires(I it, typename I::difference_type n) {
        { it + n } -> std::same_as<I>;
        { it - n } -> std::same_as<I>;
        { it += n } -> std::same_as<I &>;
        { it -= n } -> std::same_as<I &>;
        { it[n] } -> std::same_as<typename I::reference>;
    };

    template <typename I>
    concept Distance = requires(I it1, I it2) {
        { it2 - it1 } -> std::convertible_to<typename I::difference_type>;
    };

    template <typename I>
    concept RandomAccessIterator = BidirectionalIterator<I> &&
                                   RandomAccess<I> && Distance<I> &&
                                   DerivedFrom<typename I::iterator_category, std::bidirectional_iterator_tag>;
};

#endif // __ITERATOR_CONCEPTS_H__