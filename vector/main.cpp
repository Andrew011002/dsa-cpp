#include "vector.hpp"
#include <cstdio>

int main() {
  vector<int> v(10);
  v.append(15);
  v.append(13);
  v.append(20);
  v.print();
  v.resize();
  printf("%ld\n", v.capacity());
  v.print();
  return 0;
}
