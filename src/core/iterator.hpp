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
    using IteratorCategory  = Category;
    using ValueType         = T;
    using DifferenceType    = Distance;
    using PointerType       = Pointer;
    using ReferenceType     = Reference;
};

template<class I>
struct IteratorTraits {
    using IteratorCategory  = typename I::IteratorCategory;
    using ValueType         = typename I::ValueType;
    using DifferenceType    = typename I::DifferenceType;
    using PointerType       =  typename I::PointerType;
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
inline ForwardIteratorTag iteratorCategory(const ForwardIterator<T, Distance>&)
{ return ForwardIteratorTag(); }

template <class T, class Distance> 
inline BidirectionalIteratorTag iteratorCategory(const BidirectionalIterator<T, Distance>&){ 
    return BidirectionalIteratorTag(); 
}

template <class T, class Distance>
inline RandomAccessIteratorTag iteratorCategory(const RandomAccessIterator<T, Distance>&) { 
    return RandomAccessIteratorTag(); 
}

template <class I, class Distance>
inline void advance(I& i, Distance n, InputIteratorTag) {
    while (n--) {
        ++i;
    }
}

template <class I, class Distance>
inline void advance(I& i, Distance n, BidirectionalIteratorTag) {
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

template<class ForwardIterator, class T>
void uninitializedFill(ForwardIterator first, ForwardIterator last, const T& x) {
    
}

template<class ForwardIterator, class Size, class T>
void uninitializedFillN(ForwardIterator first, Size n, const T& x) {
    return __uninitialized_fill_n(first, n, x, value_type(first));
}


template<class ForwardIterator, class Size, class T, class T1>
void __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1) {
    return __uninitialized_fill_n_aux(first, n, x, std::is_pod<T>());
}

template<class ForwardIterator, class Size, class T>
void __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, std::false_type) {
    
}

template<class ForwardIterator, class Size, class T>
void __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, std::true_type) {
}

}
