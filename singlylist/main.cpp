#include "singlylist.hpp"
#include <cstdio>

int main() {
  auto list = singlylist<int>();
  for (int i = 0; i < 10; i++) {
    list.add(i);
  }
  list.add(2);
  list.add(2);
  list.add(11);
  list.print();
  printf("Count of %d is %d\n", 2, list.count(2));
  printf("Count of %d is %d\n", 0, list.count(0));
  printf("Count of %d is %d\n", 15, list.count(15));

  printf("Index of %d starting at %d is %d\n", 5, 10, list.find(5, 10));
}
