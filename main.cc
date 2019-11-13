#include <iostream>
#include "src/core/iterator.hpp"
#include "src/vector.hpp"
#include <vector>
//#inlcude <allocator>

int main() {
    auto alloc = std::allocator<int>();
    auto ints = alloc.allocate(10);
    alloc.deallocate(ints, 10);
}
