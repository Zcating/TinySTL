#include <iostream>
#include "src/vector.hpp"
#include "src/list.hpp"
//#inlcude <allocator>
//#include <vector>
#include <list>
//struct TestData {
//    int val;
//    int val2;
//    TestData(int val = 1, int val2 = 2): val(val), val2(val2) {}
//};

int main() {
    //auto vec = tinystd::Vector<TestData>(10, TestData());
    //vec.push(TestData(10, 20));
    //for (auto i = 0; i < vec.size(); i++) {
    //    //printf("%d \n", vec[i]);
    //    printf("%d %d \n", vec[i].val, vec[i].val2);
    //}
    //printf("capacity = %d\n", vec.capacity());

    auto list = std::list<int>();
    list.push_front(1);
    for (auto i = list.begin(); i != list.end(); i++)
    {
        printf("i.data = %d\n", *i);
    }

    system("pause");
}
