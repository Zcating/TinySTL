#include <iostream>
#include "src/vector.hpp"
//#inlcude <allocator>
#include <vector>

int main() {
    auto vec = tinystd::Vector<int>(10, 0);
    for (int i = 0; i < vec.size(); i++) {
        printf("%d \n", vec[i]);
    }
    system("pause");
}
