#include "array.hpp"
#include <cstdio>

int main() {
    array<int> arr(10);
    arr.add(15);
    arr.add(1);
    arr.add(12);
    arr.add(14);
    arr.print();
    printf("size: %lu, capacity: %lu\n", arr.size(), arr.capacity());
    return 0;
}

