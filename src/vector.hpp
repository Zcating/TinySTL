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
    AllocType allocator;

    void insertAux(Iterator position, ConstReference value) {
        if (finish != endOfStorage) {
            construct(finish, *(finish - 1));
            ++finish;
            auto valueCopy = value;
            std::copy_backward(position, finish - 2, finish - 1);
            *position = valueCopy;
        }
        else {
            const auto oldSize = size();
            // if old size is 0, let it configure to 1
            // if old size is not 0, let it configure to its 2 times.
            const auto length = oldSize != 0 ? 2 * oldSize : 1;
            auto newStart = allocator.allocate(length);
            auto newFinish = newStart;
            try {
                newFinish = uninitializedCopy(start, position, newStart);
                construct(newFinish, value);
                ++newFinish;
                newFinish = uninitializedCopy(position, finish, newFinish);
            }
            catch (...) {
                destroy(newStart, newFinish);
                allocator.deallocate(newStart, length);
            }

            // destruct & release
            destroy(start, finish);
            deallocate();

            // adjust iterator, point to new one
            start = newStart;
            finish = newFinish;
            endOfStorage = newStart + length;
        }
    };
    
    void insert(Iterator position, SizeType n, ConstReference x) {
        if (n == 0) {
            return;
        }
        if (SizeType(endOfStorage - finish) >= n) {
            auto xCopy = x;
            const auto elementAfter = finish - position;
            auto oldFinish = finish;
            if (elementAfter > n) {
                uninitializedCopy(finish - n, finish, finish);
                finish += n;
                std::copy_backward(position, oldFinish - n, oldFinish);
                uninitialized_fill(position, oldFinish, xCopy);
            }
        }
        else {
            const auto oldSize = size();
            // if old size is 0, let it configure to 1
            // if old size is not 0, let it configure to its 2 times.
            const auto length = oldSize != 0 ? 2 * oldSize : 1;
            auto newStart = Allocator::allocate(length);
            auto newFinish = newStart;
            try {
                newFinish = uninitializedCopy(start, position, newStart);
                newFinish = uninitialized_fill_n(newFinish, n, x);
                newFinish = uninitializedCopy(position, finish, newFinish);
            }
            catch (...) {
                destroy(newStart, newFinish);
                allocator.deallocate(newStart, length);
                throw;
            }
            destroy(start, finish);
            deallocate();
            start = newStart;
            finish = newFinish;
            endOfStorage = newStart + length;
        }
    }



    // 
    void fillInitialize(SizeType n, ConstReference value) {
        start = allocator.allocate(n);
        std::fill_n(start, n, value);
        finish = start + n;
        endOfStorage = finish;
    }

    Iterator erase(Iterator position) {
        if (position + 1 != end()) {
            std::copy(position + 1, finish, position);
        }
        finish -= 1;
        destroy(finish);
        return position;
    }

    Iterator erase(Iterator first, Iterator last) {
        auto i = std::copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last - first);
        return first;
    }

    void deallocate() {
        if (start) {
            allocator.deallocate(start, endOfStorage - start);
        }
    }
        
public:
    Vector(): start(0), finish(0), endOfStorage(0) {};

    Vector(SizeType n, ConstReference value): allocator(AllocType()) {
        fillInitialize(n, value);
    };
    Vector(int n, ConstReference value) : allocator(AllocType()) {
        fillInitialize(n, value);
    }

    Vector(long n, ConstReference value) : allocator(AllocType()) {
        fillInitialize(n, value);
    }

    //Vector(const std::initializer_list<T> &iList) : Allocator(AllocType()) {
    //    start = alloc.allocate(iList.size());
    //}

    explicit Vector(SizeType n) : allocator(AllocType()) {
        fillInitialize(n, T());
    }

    ~Vector() {
        destroy(start, finish);
        deallocate();
    }
    
    Iterator begin() const { return start; }
    
    Iterator end() const { return finish; }
    
    SizeType size() const { return SizeType(end() - begin()); }

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

    void push(ConstReference x) {
        if (finish != endOfStorage) {
            construct(finish, x);
            finish += 1;
        }
        else {
            insertAux(end(), x);
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

    void clear() {
        erase(begin(), end());
    }
};

}
