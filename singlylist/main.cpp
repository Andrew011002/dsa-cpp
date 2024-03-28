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
  list.remove(2, 2);
  list.remove(2);
  list.print();
}
