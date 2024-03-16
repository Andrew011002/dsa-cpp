#include "vector.hpp"
#include <cstdio>

int main() {
  vector<int> v(10);
  printf("size: %ld\n", v.size());
  v.append(15);
  printf("size: %ld\n", v.size());
  v.append(13);
  v.append(20);
  printf("size: %ld\n", v.size());
  v.print();
  v.insert(0, 10);
  printf("contains %d? %d\n", 10, v.contains(10));
  printf("contains %d? %d\n", 1, v.contains(1));
  v.resize();
  v.print();
  return 0;
}
