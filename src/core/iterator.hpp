struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomIteratorTag : public BidirectionalIteratorTag {};

template<class Category, class T, class Distance = int, class Pointer = T*, class Reference = T&>
struct Iterator {
    typename IteratorCategory = Category;
    typename ValueType = T;
    typename DifferenceType = Distance;
    typename PointerType = Pointer;
    typename ReferenceType = Reference;
}

template<class I>
struct IteratorTraits {
    typedef typename I::IteratorCategory    IteratorCategory;
    typedef typename I::ValueType           ValueType;
    typedef typename I::DifferenceType      DifferenceType;
    typedef typename I::PointerType         PointerType;
    typedef typename I::ReferenceType       ReferenceType;
}

template<class T>
struct IteratorTraits {

};

