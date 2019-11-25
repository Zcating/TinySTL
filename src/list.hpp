#pragma once
#include "core/allocator.hpp"
#include "core/iterator.hpp"

namespace tinystd 
{
    template<class T>
    struct ListNode {
        using VoidPointer = void*;
        VoidPointer prev;
        VoidPointer next;
        T data;
    };

    template<class T, class R, class P>
    struct ListIterator
    {
        using Iterator = ListIterator<T, T&, T*>;
        using Self = ListIterator<T, R, P>;

        using IteratorCategory = BidirectionalIteratorTag;
        using ValueType = T;
        using Pointer = P;
        using Reference = R;
        using LinkType = ListNode<T>*;
        using SizeType = size_t;
        using DifferenceType = ptrdiff_t;


        LinkType node;

        ListIterator(LinkType x): node(x) {};

        ListIterator() {};

        ListIterator(const Iterator& x): node(x.node) {}

        bool operator==(const Self& x) const { return node == x.node; }
        bool operator!=(const Self& x) const { return node != x.node; }

        Reference operator*() const { return (*node).data; }

        Pointer operator->() const { return &(operator*()); }


    };
    template<class T, class Allocator = tinystd::Allocator>
    
}