#include "array.hpp"

int main() {
  array<int> arr;

  std::cout << "Empty? " << (arr.empty() ? "Yes\n" : "No\n");

  arr.add(10);
  arr.add(5);
  arr.add(20);
  arr.add(20);
  arr.add(20);

  std::cout << "\nInteger Array:\n";
  arr.print();

  arr.modify(2, 35);
  std::cout << "Get element at index 2: " << arr.get(2) << std::endl;
  std::cout << "Contains 5? " << (arr.contains(5) ? "Yes\n" : "No\n");

  std::cout << "Index of 20: " << arr.find(20) << std::endl;
  std::cout << "Index of 20 (start = -1): " << arr.find(20, -1) << std::endl;
  std::cout << "Index of 0: " << arr.find(0) << std::endl;
  std::cout << "Count of 20: " << arr.count(20) << "\n\n";

  arr.remove(5);
  arr.removeall(20);
  std::cout << "After removals:\n";
  arr.print();

  arr.insert(0, 7);
  std::cout << "After inserting 7 at front:\n";
  arr.print();

  std::cout << "Index 5 out of bounds? "
            << (arr.outofbounds(5) ? "Yes\n" : "No\n");
  std::cout << "Index -1 out of bounds? "
            << (arr.outofbounds(-1) ? "Yes\n" : "No\n");

  std::cout << "Size: " << arr.size() << ", Capacity: " << arr.capacity()
            << std::endl;
  std::cout << "Full? " << (arr.full() ? "Yes\n" : "No\n");
  int n = arr.capacity() - arr.size();
  for (int i = 0; i < n; i++) {
    arr.add((i + 1) * 10);
  }
  std::cout << "Full? " << (arr.full() ? "Yes\n" : "No\n");
  arr.print();

  arr.clear();
  arr.print();

  return 0;
}
