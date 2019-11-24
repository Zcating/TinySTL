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
    __destroy(first, last, valueType(first));
}

// Aux function
template<class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T) {
    __destroyAux(first, last, std::is_trivially_destructible<T>());
}

// Element has trival destructor.
template<class ForwardIterator>
inline void __destroyAux(ForwardIterator first, ForwardIterator last, std::true_type) {}

// Element has non trival destructor.
template<class ForwardIterator>
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
inline auto uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
    return __uninitialized_fill_n(first, n, x, valueType(first));
}


template<class ForwardIterator, class Size, class T, class T1>
inline auto __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1) {
    return __uninitialized_fill_n_aux(first, n, x, std::is_pod<T>());
}

template<class ForwardIterator, class Size, class T>
inline auto __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, std::false_type) {
    return std::fill_n(first, n, x);
}

template<class ForwardIterator, class Size, class T>
auto __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, std::true_type) {
    auto cur = first;
    for (; n > 0; --n, ++cur) {
        construct(&*cur, x);
    }
    return cur;
}



template<class InputIterator, class ForwardIterator>
inline ForwardIterator uninitializedCopy(InputIterator first, InputIterator last, ForwardIterator result) {
    return __uninitializedCopy(first, last, result, valueType(result));
}

template<class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __uninitializedCopy(InputIterator first, InputIterator last, ForwardIterator result, T*) {
    return __uninitializedCopyAux(first, last, result, std::is_pod<T>());
}

template<class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitializedCopyAux(InputIterator first, InputIterator last, ForwardIterator result, std::true_type) {
    return std::copy(first, last, result);
}

template<class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitializedCopyAux(InputIterator first, InputIterator last, ForwardIterator result, std::false_type) {
    auto cur = result;
    for (auto start = first; start != last; ++start, ++cur) {
        construct(&*cur, *start);
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