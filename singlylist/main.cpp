#include "singlylist.hpp"

int main() {
  auto list = singlylist<int>();
  list.add(1);
  list.add(2);
  list.add(3);
  list.print();
}
