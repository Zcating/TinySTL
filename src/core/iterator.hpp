#include <cstddef>
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct Iterator {
    typename IteratorCategory = Category;
    typename ValueType = T;
    typename DifferenceType = Distance;
    typename PointerType = Pointer;
    typename ReferenceType = Reference;
};

template<class I>
struct IteratorTraits {
    typedef typename I::IteratorCategory    IteratorCategory;
    typedef typename I::ValueType           ValueType;
    typedef typename I::DifferenceType      DifferenceType;
    typedef typename I::PointerType         PointerType;
    typedef typename I::ReferenceType       ReferenceType;
};

template<class T>
struct IteratorTraits<T*> {
    typedef RandomAccessIteratorTag IteratorCategory;
    typedef T ValueType;
    typedef ptrdiff_t DifferenceType;
    typedef T* PointerType;
    typedef T& ReferenceType;
};


template<class T>
struct IteratorTraits<const T*> {
    typedef RandomAccessIteratorTag IteratorCategory;
    typedef T ValueType;
    typedef ptrdiff_t DifferenceType;
    typedef const T* PointerType;
    typedef const T& ReferenceType;
};

// decide the distance type
template<class I>
inline typename IteratorTraits<I>::IteratorCategory distanceType(const I&) {
    return static_cast<typename IteratorTraits<I>::DifferenceType*>(0);
}


// decide the value type
template<class I>
inline typename IteratorTraits<I>::IteratorCategory valueType(const I&) {
    return static_cast<typename IteratorTraits<I>::ValueType*>(0);
}


