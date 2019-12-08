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
        using SizeType = size_t;
        using DifferenceType = ptrdiff_t;

        using LinkType = ListNode_<T> *;


        LinkType node;

        ListIterator_(LinkType x): node(x) {
        };

        ListIterator_() {};

        ListIterator_(const Iterator& x): node(x.node) {}

        bool operator == (const Self& x) const { return node == x.node; }
        bool operator != (const Self& x) const { return node != x.node; }

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

    template<class T>
    class List
    {
        using ListNode = ListNode_<T>;

        using ValueType = T;
        using Iterator = ListIterator_<T, T&, T*>;
        using ConstIterator = const T*;
        using Reference = T & ;
        using ConstReference = const T&;
        using AllocatorType = Allocator<ListNode>;
        using SizeType = size_t;
        using DifferenceType = ptrdiff_t;

    public:
        using LinkType = ListNode *;
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

        void pushFront(ConstReference x) {
            insert(begin(), x);
        }

        void pushBack(ConstReference x) {
            insert(end(), x);
        }

        auto erase(Iterator position) -> decltype(position) {
            auto nextNode = LinkType(position.node->next);
            auto prevNode = LinkType(position.node->prev);
            auto 
        }

        Iterator insert(Iterator position, ConstReference x) {
            auto tmp = createNode(x);
            tmp->next = position.node;
            tmp->prev = position.node->prev;
            (LinkType(position.node->prev))->next = tmp;
            position.node->prev = tmp;
            return tmp;
        }


    private: 
        LinkType getNode() {
            return allocator.allocate(1);
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