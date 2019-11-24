#include <iostream>
#include "src/vector.hpp"
//#inlcude <allocator>
#include <vector>

struct Fucker {
    int val;
    int val2;
    Fucker(int val = 1, int val2 = 2): val(val), val2(val2) {}
};

int main() {
    /*auto fuck = std::enable_if<std::is_destructible<std::string>::value>();*/
    auto vec = tinystd::Vector<Fucker>(10, Fucker());
    vec.push(Fucker(10, 20));
    for (auto i = 0; i < vec.size(); i++) {
        //printf("%d \n", vec[i]);
        printf("%d %d \n", vec[i].val, vec[i].val2);
    }

    printf("capacity = %d\n", vec.capacity());
    system("pause");
}
