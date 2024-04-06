#include "doublylist.hpp"
#include <ostream>

int main() {
  doublylist<int> list;
  list.append(3);
  list.append(4);
  list.append(1);
  list.append(2);

  for (auto it = list.begin(); it != list.end(); ++it) {
    it->key = 10;
  }
  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << std::endl;
  }
  return 0;
}
