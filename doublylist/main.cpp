#include "doublylist.hpp"
#include <cstdio>

int main() {
  doublylist<int> list;
  list.append(3);
  list.append(4);
  list.append(1);
  list.append(2);

  for (auto i = list.begin(); i != list.end(); ++i) {
    printf("%d\n", *i);
  }
  return 0;
}
