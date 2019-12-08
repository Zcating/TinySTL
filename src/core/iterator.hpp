#pragma once

#include <cstddef>
#include <type_traits>
namespace tinystd
{

// Iterator category
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

// Iterator defination
template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct Iterator { 
    using IteratorCategory  = typename Category;
    using ValueType         = typename T;
    using DifferenceType    = typename Distance;
    using PointerType       = typename Pointer;
    using ReferenceType     = typename Reference;
};

// Type extraction
template<class I>
struct IteratorTraits {
    using IteratorCategory  = typename I::IteratorCategory;
    using ValueType         = typename I::ValueType;
    using DifferenceType    = typename I::DifferenceType;
    using PointerType       = typename I::PointerType;
    using ReferenceType     = typename I::ReferenceType;
};

// T* Partial Specialization
template<class T>
struct IteratorTraits<T*> {
    using IteratorCategory  = RandomAccessIteratorTag;
    using ValueType         = typename T;
    using DifferenceType    = ptrdiff_t;
    using PointerType       = typename T*;
    using ReferenceType     = typename T&;
};

// const T* Partial Specialization
template<class T>
struct IteratorTraits<const T*> {
    using IteratorCategory = RandomAccessIteratorTag;
    using ValueType = typename T;
    using DifferenceType = ptrdiff_t;
    using PointerType = typename const T*;
    using ReferenceType = typename const T&;
};


template<class T, class Distance = ptrdiff_t>
struct InputIterator: public Iterator<InputIteratorTag, T, Distance> {};

template<class T, class Distance = ptrdiff_t>
struct OutputIterator: public Iterator<OutputIteratorTag, T, Distance> {};

template<class T, class Distance = ptrdiff_t>
struct ForwardIterator: public Iterator<ForwardIteratorTag, T, Distance> {};

template<class T, class Distance = ptrdiff_t>
struct BidirectionalIterator: public Iterator<BidirectionalIteratorTag, T, Distance> {};

template<class T, class Distance = ptrdiff_t>
struct RandomAccessIterator: public Iterator<RandomAccessIteratorTag, T, Distance> {};


template <class T, class Distance> 
inline InputIteratorTag iteratorCategory(const InputIterator<T, Distance>&) { 
    return InputIteratorTag(); 
}


template <class T, class Distance> 
inline OutputIteratorTag iteratorCategory(const OutputIterator<T, Distance>&) { 
    return OutputIteratorTag(); 
}

template <class T, class Distance> 
inline ForwardIteratorTag iteratorCategory(const ForwardIterator<T, Distance>&){ 
    return ForwardIteratorTag(); 
}

template <class T, class Distance> 
inline BidirectionalIteratorTag iteratorCategory(const BidirectionalIterator<T, Distance>&){ 
    return BidirectionalIteratorTag(); 
}

template <class T, class Distance>
inline RandomAccessIteratorTag iteratorCategory(const RandomAccessIterator<T, Distance>&) { 
    return RandomAccessIteratorTag(); 
}

template <class I, class Distance>
void advance(I& i, Distance n, InputIteratorTag) {
    while (n--) {
        ++i;
    }
}

template <class I, class Distance>
void advance(I& i, Distance n, BidirectionalIteratorTag) {
    if (n >= 0) {
        while (n--) {
            ++i;
        }
    } else {
        while (n++) {
            --i;
        }
    }
}

template <class I, class Distance>
inline void advance(I& i, Distance n, RandomAccessIteratorTag) {
    i += n;
}

template <class InputIter, class Distance>
inline void advance(InputIter& i, Distance n) {
    advance(i, n, iteratorCategory(i));
}

template <class Iterator>
inline auto valueType(const Iterator &) {
    return static_cast<typename IteratorTraits<Iterator>::ValueType*>(0);
}


template<class InputIterator>
inline auto distance(InputIterator first, InputIterator last) {
    using Category = IteratorTraits<InputIterator>::IteratorCategory;
    return __distance(first, last, Category());
}

template<class InputIterator>
auto __distance(InputIterator first, InputIterator last, InputIteratorTag) {
    IteratorTraits<Iterator>::DifferenceType n = 0;
    while (first != last) {
        first++;
        n++;
    }
    return n;
}

template<class InputIterator>
inline auto __distance(InputIterator first, InputIterator last, RandomAccessIteratorTag) -> decltype(last - first) {
    return last - first;
}

}
