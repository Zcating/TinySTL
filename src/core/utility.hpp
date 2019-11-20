#pragma once

namespace tinystd
{

/*    
    construct function of placement new
*/
template<class T1, class T2>
inline void construct(T1* pointer, const T2& value) {
    new (pointer)T1(value);
}

/*
    Destroy function
 */

// First version, accept the pointer type of T.
// 
template<class T>
inline void destroy(T* pointer) {
    pointer->~T();
}


// Second version, accept the iterator. 
// This function will find the element's type.
template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    __destroy(first, last, ForwardIterator::ValueType(first));
}

// Aux function
template<class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T) {
    using TrivalDestructor = std::is_trivially_destructible<T>;
    __destroyAux(first, last, TrivalDestructor());
}

// Element has trival destructor.
template<class ForwardIterator, class T>
inline void __destroyAux(ForwardIterator first, ForwardIterator last, std::true_type) {}

// Element has non trival destructor.
template<class ForwardIterator, class T>
inline void __destroyAux(ForwardIterator first, ForwardIterator last, std::false_type) {
    for (auto index = first; index < last; ++index) {
        destroy(&*index);
    }
}


//
// Specialized 'destroy' function for the second version.
// char* & wchat_t*
inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}



template<class ForwardIterator, class Size, class T>
inline void uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
    return __uninitialized_fill_n(first, n, x, value_type(first));
}


template<class ForwardIterator, class Size, class T, class T1>
inline void __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1) {
    return __uninitialized_fill_n_aux(first, n, x, std::is_pod<T>());
}

template<class ForwardIterator, class Size, class T>
inline void __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, std::false_type) {
    return std::fill_n(first, n, x);
}

template<class ForwardIterator, class Size, class T>
void __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, std::true_type) {
    auto cur = first;
    for (; n > 0; --n; ++cur) {
        construct(&*cur, x);
    }
    return cur;
}



template<class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
    return uninitialized_copy(first, last, result, ForwardIterator::ValueType(result));
}

template<class InputIterator, class ForwardIterator, class T>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*) {
    return __uninitialized_copy(first, last, std::is_pod<T>());
}

template<class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, std::true_type) {
    return std::copy(first, last, result);
}

template<class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, std::false_type) {
    auto cur = first;
    for (; first != last; ++first, ++cur) {
        construct(&*cur, *first);
    }
    return cur;
}

/*
 *    uninitialized_fill
 */
template<class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x) {
    uninitialized_fill(first, last, x, ForwardIterator::ValueType(first));
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, T*) {
    __uninitialized_fill(first, last, x, std::is_pod<T>());
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, std::true_type) {
    std::fill(first, last, x);
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, std::false_type) {
    auto cur = first;
    for (; cur != last; ++cur) {
        construct(&*cur, x);
    }
}

}