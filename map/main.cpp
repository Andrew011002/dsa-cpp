#include "map.hpp"
#include <cstdio>
#include <string>

int main() {
  node<std::string, int> n("hello");
  printf("key: %s, value: %d\n", n.key.data(), n.value.value());
  return 0;
}
