#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
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
  void remove(T elem);
  void remove(T elem, std::uint32_t n);
  void removeall(T elem);
  void insert(int index, T elem);
  bool contains(T elem) const;
  std::uint32_t count(T elem) const;
  int find(T elem) const;
  int find(T elem, int start) const;
  std::uint32_t toindex(int index) const;
  bool outofbounds(int index) const;
  bool empty() const;
  bool full() const;
  std::size_t size() const;
  std::size_t capacity() const;
  void print() const;
};

template <typename T>
array<T>::array() : arrptr(new T[8]), iptr(arrptr), msize(0), mcapacity(8) {}

template <typename T>
array<T>::array(std::size_t capacity)
    : arrptr(new T[capacity]), iptr(arrptr), msize(0), mcapacity(capacity) {}

template <typename T> T array<T>::get(int index) const {
  if (empty()) {
    std::cout << "empty here\n";
    throw new std::exception();
  }
  if (outofbounds(index)) {
    std::cout << "oob here\n";
    throw new std::exception();
  }
  index = toindex(index);
  return *(arrptr + index);
}

template <typename T> void array<T>::add(T elem) {
  if (full()) {
    throw new std::exception();
  }
  *iptr = elem;
  iptr++;
  msize++;
}

template <typename T> void array<T>::remove(T elem) {
  if (empty()) {
    throw new std::exception();
  }
  T *ptr = arrptr;
  int index = 0;
  while (index < size() && *ptr != elem) {
    ptr++;
    index++;
  }
  if (*ptr != elem) {
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

template <typename T> void array<T>::remove(T elem, std::uint32_t n) {
  if (empty()) {
    throw std::exception();
  }
  while (contains(elem) && n > 0) {
    remove(elem);
    n--;
  }
}

template <typename T> void array<T>::removeall(T elem) {
  if (empty()) {
    throw new std::exception();
  }
  std::uint32_t elemcount = count(elem);
  if (elemcount == 0) {
    throw new std::exception();
  }
  remove(elem, elemcount);
}

template <typename T> void array<T>::insert(int index, T elem) {
  if (full()) {
    throw new std::exception();
  }
  if (outofbounds(index)) {
    throw new std::exception();
  }
  index = toindex(index);
  T *ptr = arrptr + index;
  for (int i = index; i < size() + 1; i++) {
    T tmp = *ptr;
    *ptr++ = elem;
    elem = tmp;
  }
  iptr = ptr;
  msize++;
}

template <typename T> bool array<T>::contains(T elem) const {
  T *ptr = arrptr;
  for (int i = 0; i < size(); i++) {
    if (*ptr++ == elem) {
      return true;
    }
  }
  return false;
}

template <typename T> std::uint32_t array<T>::count(T elem) const {
  T *ptr = arrptr;
  std::uint32_t elemcount = 0;
  for (int i = 0; i < size(); i++) {
    if (*ptr++ == elem) {
      elemcount++;
    }
  }
  return elemcount;
}

template <typename T> int array<T>::find(T elem) const { return find(elem, 0); }

template <typename T> int array<T>::find(T elem, int start) const {
  if (outofbounds(start)) {
    throw new std::exception();
  }
  start = toindex(start);
  T *ptr = arrptr + start;
  for (int i = start; i < size(); i++) {
    if (*ptr++ == elem) {
      return i;
    }
  }
  return -1;
}

template <typename T> bool array<T>::outofbounds(int index) const {
  return (abs(index) > size());
}

template <typename T> std::uint32_t array<T>::toindex(int index) const {
  if (index < 0) {
    return size() + index;
  }
  return index;
}

template <typename T> bool array<T>::empty() const { return msize == 0; }

template <typename T> bool array<T>::full() const { return msize == mcapacity; }

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
