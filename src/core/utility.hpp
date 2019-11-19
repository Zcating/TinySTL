#pragma once

namespace tinystd
{

template<class T1, class T2>
inline void construct(T1* pointer, const T2& value) {
    new (pointer)T1(value);
}


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


/*
    * Specialized 'destroy' function for the second version.
    * char* & wchat_t*
    */
inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}

}