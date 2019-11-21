#pragma once
#include <cstddef>
#include <iostream>
#include <type_traits>

namespace tinystd
{

//template<class T>
//inline auto _allocate(ptrdiff_t size, T*) {
//    
//}
//
//
template<class T>
class Allocator {
public:
    using ValueType = T;
    using Pointer = T*;
    using ConstPointer = const T*;
    using Reference = T&;
    using ConstReference = const T&;
    using SizeType = size_t;
    using DifferenceType = ptrdiff_t;

    Pointer allocate(SizeType n, const void* hint = 0) {
        auto tmp = (T*)(new (size_t)(n * sizeof(T)));
        if (tmp == 0) {
            std::cerr << "out of memery." << std::endl;
            exit(1);
        }
        return tmp;
    }


    void deallocate(Pointer ptr) {
        delete ptr;
    }
};

}