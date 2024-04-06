#include "doublylist.hpp"
#include <iostream>

int main() {
  doublylist<int> list;
  list.append(3);
  list.append(4);
  list.insert(0, 5);
  list << std::cout << std::endl;
  list.insert(3, 15);
  list << std::cout << std::endl;
  list.insert(1, 8);
  list << std::cout << std::endl;
  list.insert(3, 16);
  list << std::cout << std::endl;
  list.update(1, 20);
  std::cout << list.get(1) << std::endl;
  list.update(-2, 21);
  std::cout << list.get(-2) << std::endl;
  list.print();
  return 0;
}
