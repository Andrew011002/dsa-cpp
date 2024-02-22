#include "array.hpp"
#include <cstdio>

int main() {
    array<int> arr(10);
    arr.add(15);
    arr.add(1);
    arr.add(12);
    arr.add(14);
    arr.add(12);
    arr.add(15);
    arr.remove(12);
    arr.insert(0, 21);
    printf("count for 12: %d\n", arr.count(12));
    printf("count for 15: %d\n", arr.count(15));
    arr.insert(6, 20);
    arr.insert(-5, 2);
    arr.print();
    arr.removeall(12);
    arr.add(15);
    arr.remove(15, 2);
    arr.print();
    printf("size: %lu, capacity: %lu\n", arr.size(), arr.capacity());
    return 0;
}

