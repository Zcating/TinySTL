#include <cstddef>
#include "core/iterator.hpp"

namespace tinystd {

    template<class T>
    class Vector {
    public: 
        using ValueType = T;
        using Iterator = T*;
        using ConstIterator = const T*;
        using Reference = T&;
        using ConstReference = const T&;

        using SizeType = std::size_t;
        using DifferenceType = ptrdiff_t;

        Vector() = default;
        ~Vector();

        Iterator begin() const;
        Iterator end() cosnt;
        SizeType size() const;
        ValueType& operator[](SizeType index) const;
        ValueType& at(SizeType index) const;
        void push(const ValueType& newElement);
        void pop(const ValueType& newElement);

    }

}