#include "singlylist.hpp"
#include <cstdio>

int main() {
  auto list = singlylist<int>();
  list.add(15);
  printf("Item at %d is %d\n", 0, list.get(0));
  printf("Item at %d is %d\n", -1, list.get(-1));
  list.update(11, 0);
  list.print();
  list.update(12, -1);
  list.print();
}
