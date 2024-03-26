#include "singlylist.hpp"
#include <cstdio>

int main() {
  auto list = singlylist<int>();
  list.add(1);
  list.add(2);
  list.add(3);
  list.remove(1);
  list.insert(5, 0);
  list.print();
  list.insert(10, 1);
  list.print();
  list.insert(11, 4);
  list.print();
  list.remove(11);
  list.print();
  list.remove(10);
  list.insert(15, 1);
  list.print();
  list.insert(100, 0);
  list.print();
  printf("Contains %d: %d\n", 100, list.contains(100));
  printf("Contains %d: %d\n", 15, list.contains(15));
  printf("Contains %d: %d\n", 11, list.contains(11));
  printf("Length: %d\n", list.length());
}
