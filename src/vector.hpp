#include <cstddef>
#include "core/iterator.hpp"

#include <allocators>

namespace tinystd 
{

template<class T, class Alloc = std::allocator<T>>
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

        
public:
    Vector(): start(0), finish(0), endOfStorage(0) {};
    Vector(SizeType n, ConstReference value): alloc(AllocType()) {
        start = alloc.allocate(n);
        finish = start + n;
    };
    ~Vector();
    Iterator begin() const;
    Iterator end() cosnt;
    SizeType size() const;
    Reference operator[](SizeType index) const;
    Reference at(SizeType index) const;
    void push(const Reference newElement);
    void pop(const Reference newElement);
}

};
