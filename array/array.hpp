#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>

template <typename T> class array {
  T *arrptr;
  T *iptr;
  std::size_t msize;
  std::size_t mcapacity;

public:
  array();
  array(std::size_t capacity);
  T get(int index) const;
  void modify(int index, T elem);
  void add(T elem);
  void remove(T elem, std::uint32_t n);
  void remove(T elem);
  void insert(int index, T elem);
  bool empty() const;
  std::size_t size() const;
  std::size_t capacity() const;
  void print() const;
};

template <typename T>
array<T>::array() : arrptr(new T[10]), iptr(arrptr), msize(0), mcapacity(10) {}

template <typename T>
array<T>::array(std::size_t capacity)
    : arrptr(new T[capacity]), iptr(arrptr), msize(0), mcapacity(capacity) {}

template <typename T> T array<T>::get(int index) const {
  if (size() == 0) {
    throw new std::exception();
  }
  return *(arrptr + index);
}

template <typename T> void array<T>::add(T elem) {
  if (size() == capacity()) {
    throw new std::exception();
  }
  *iptr = elem;
  iptr++;
  msize++;
}

template <typename T> void array<T>::remove(T elem) {
  if (size() == 0) {
    throw new std::exception();
  }
  T *ptr = arrptr;
  int index = 0;
  while (index < size() && *ptr != elem) {
    ptr++;
    index++;
  }
  bool found = *ptr == elem;
  if (found == false) {
    throw new std::exception();
  }
  while (index < size() - 1) {
    *ptr = *(ptr + 1);
    ptr++;
    index++;
  }
  *ptr = T();
  iptr = ptr;
  msize--;
}

template <typename T> bool array<T>::empty() const { return msize == 0; }

template <typename T> std::size_t array<T>::size() const { return msize; }

template <typename T> std::size_t array<T>::capacity() const {
  return mcapacity;
}

template <typename T> void array<T>::print() const {
  T *ptr = arrptr;
  std::cout << "[";
  for (int i = 0; i < size(); i++) {
    std::cout << *ptr++;
    if (i < size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]\n";
}
