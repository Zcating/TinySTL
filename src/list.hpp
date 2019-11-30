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
        using LinkType = ListNode_<T> *;
        using SizeType = size_t;
        using DifferenceType = ptrdiff_t;

    public:

        LinkType node;

        ListIterator(LinkType x): node(x) {
        };

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
        using SizeType = size_t;
        using DifferenceType = ptrdiff_t;

    public:
        using LinkType = ListNode*;

        AllocatorType allocator;
        LinkType node;

        List() : allocator(AllocatorType()) {
            emptyInit();
        }

        ~List() {}
        Iterator begin() { return (LinkType)(*node).next; }
        Iterator end() { return node; }

        bool empty() const { return node->next == node; }

        SizeType size() const {
            return distance(begin(), end());
        }

        Reference front() {
            return *begin();
        }

        Reference back() {
            return *(--end());
        }

        pushFront(ConstReference x) {
            
        }

    private: 
        LinkType getNode() {
            return allocator.allocate();
        }
        void putNode(LinkType node) {
            allocator.deallocate(node);
        }
        LinkType createNode(ConstReference x) {
            auto p = getNode();
            construct(&p->data, x);
            return p;
        }
        void destroyNode(LinkType p) {
            destroy(&p->data);
            putNode(p);
        }

        void emptyInit() {
            node = getNode();
            node->next = node;
            node->prev = node;
        }
    };
}