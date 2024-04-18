#include "map.hpp"
#include <cstdio>

int main() {
  map<std::string, int> m;
  std::cout << m.get("hello").has_value() << std::endl;
  return 0;
}
