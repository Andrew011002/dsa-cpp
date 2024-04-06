#include "doublylist.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>

int main() {
  doublylist<int> list;
  list.append(3);
  list.append(4);
  list.append(1);
  list.append(2);

  list.update(-1, 10);
  printf("List contains %d? %d\n", 10, list.contains(10));
  printf("List contains %d? %d\n", -10, list.contains(-10));
  printf("Index of %d is %d\n", 10, list.find(10));
  printf("Index of %d is %d\n", 3, list.find(3, 1));
  printf("Index of %d is %d\n", 3, list.find(3, 0));
  return 0;
}
