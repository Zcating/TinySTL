#pragma once

#include <cstddef>
#include "core/utility.hpp"
#include "core/allocator.hpp"
#include "core/iterator.hpp"

namespace tinystd 
{

template<class T, class Alloc = Allocator<T>>
class Vector {
public: 
    using ValueType = T;
    using Iterator = T*;
    using ConstIterator = const T*;
    using Reference = T&;
    using ConstReference = const T&;

    using SizeType = std::size_t;
    using DifferenceType = ptrdiff_t;
    using AllocType = Alloc;


protected:
    Iterator start;
    Iterator finish;
    Iterator endOfStorage;
    AllocType alloc;

    void insert(Iterator position, ConstReference value) {
        if (n == 0) {
            return;
        }
        if (SizeType(endOfStorage - finish) >= n) {
            auto xCopy = x;
            auto elementsAfter = finish -position;
            auto oldFinish = finish;

            if (elementsAfter > n) {
                unini
            }
        }
    };

    // 
    void fillInitialize(SizeType n, ConstReference value) {
        start = alloc.allocate(n);
        finish = start + n;
        endOfStorage = finish;
    }

    Iterator erase(Iterator position) {
        if (position + 1 != end()) {
            copy(position + 1, finish, position);
        }
        finish -= 1;
        destroy(finish);
        return position;
    }

    Iterator erase(Iterator first, Iterator last) {
        auto i = copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last - first);
        return first;
    }
        
public:
    Vector(): start(0), finish(0), endOfStorage(0) {};

    Vector(SizeType n, ConstReference value): alloc(AllocType()) {
        fillInitialize(n, value);
    };
    Vector(int n, ConstReference value) : alloc(AllocType()) {
        fillInitialize(n, value);
    }

    Vector(long n, ConstReference value) : alloc(AllocType()) {
        fillInitialize(n, value);
    }

    explicit Vector(SizeType n) : alloc(AllocType()) {
        fillInitialize(n, T());
    }

    ~Vector() {
        alloc.deallocate(start);
    }
    
    Iterator begin() const { return start; }
    
    Iterator end() const { return finish; }
    
    SizeType size() const { return SizeType(end() - begin()) }

    SizeType capacity() const { return SizeType(endOfStorage - begin()); }

    bool empty() const {  }

    Reference operator[](SizeType index) const { return *(begin() + index); }

    Reference at(SizeType index) const { return *(begin() + index); }
    

    Reference front() {
        return *begin();
    }

    Reference back() {
        return *(end() - 1);
    }

    void push(ConstReference newElement) {
        if (finish != endOfStorage) {
            new (finish)T(newElement);
            finish += 1;
        }
        else {
            insert(end(), newElement);
        }
    }

    void popBack() {
        finish -= 1;
        destroy(finish);
    }

    void resize(SizeType newSize, ConstReference x) {
        if (newSize < size()) {
            erase(begin() + newSize, end());
        } else {
            insert(end(), newSize - size(), x);
        }
    }

    void resize(SizeType newSize) {
        resize(newSize, T());
    }

    clear() {
        erase(begin(), end());
    }
};

}
