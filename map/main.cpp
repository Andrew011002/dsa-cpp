#include "map.hpp"
#include <cstdio>
#include <string>

int main() {
  node<std::string, int> n("hello", 11);
  printf("key: %s, value: %d\n", n.key.data(), n.value.value());
  return 0;
}
