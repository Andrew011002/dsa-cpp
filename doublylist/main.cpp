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
  printf("%d\n", list.get(-1));
  return 0;
}
