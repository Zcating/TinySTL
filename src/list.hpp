#pragma once
#include "core/allocator.hpp"
#include "core/iterator.hpp"

namespace tinystd 
{
    template<class T>
    struct ListNode_ {
        using VoidPointer = void*;
        VoidPointer prev;
        VoidPointer next;
        T data;
    };

    template<class T, class R, class P>
    struct ListIterator_
    {
        using Iterator = ListIterator_<T, T&, T*>;
        using Self = ListIterator_<T, R, P>;

        using IteratorCategory = BidirectionalIteratorTag;
        using ValueType = T;
        using Pointer = P;
        using Reference = R;
        using LinkType = ListNode_<T>*;
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
        Self& operator++() {
            node = (LinkType)((*node).next);
            return *this;
        }
        Self operator++(int) {
            auto tmp = *this;
            ++*this;
            return tmp;
        }
        Self& operator--() {
            node = (LinkType)((*node).prev);
            return *this;
        }
        Self operator--(int) {
            auto tmp = *this;
            --*this;
            return tmp;
        }
    };

    template<class T, class Allocator = tinystd::Allocator<T>>
    class List
    {
        using ValueType = T;
        using Iterator = T*;
        using ConstIterator = const T*;
        using Reference = T & ;
        using ConstReference = const T&;
        using ListNode = ListNode_<T>;
        using AllocatorType = Allocator;
    public:
        using LinkType = ListNode*;

        List() {

        }
        ~List() {

        }
       
    };
}