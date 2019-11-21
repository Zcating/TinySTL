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

    void insert(Iterator position, ConstReference value) {
        if (finish != endOfStorage) {
            construct(finish, *(finish - 1));
            ++finish;
            auto valueCopy = value;
            std::copy_backward(position, finish - 2, finish - 1);
            *position = valueCopy;
        }
        else {
            const auto oldSize = size();
            const auto length = oldSize != 0 ? 2 * oldSize : 1;
            auto newStart = allocator.allocate(length);
            auto newFinish = newStart;
            try {
                newFinish = uninitialized_copy(start, position, newStart);
                construct(newFinish, value);
                ++newFinish;
                newFinish = uninitialized_copy(position, finish, newFinish);
            }
            catch (...) {
                destroy(newStart, newFinish);
                allocator.deallocate(newStart, length);
            }

            destroy(begin(), end());
            deallocate();

            start = newStart;
            finish = newFinish;
            endOfStorage = newStart + len;
        }
    };

    // 
    void fillInitialize(SizeType n, ConstReference value) {
        start = allocator.allocate(n);
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
        auto i = copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last - first);
        return first;
    }

    void deallocate() {
        allocator.deallocate(start);
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

    void clear() {
        erase(begin(), end());
    }
};

}
