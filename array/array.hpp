#include <cstdio>
#include <iostream>
#include <exception>

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
  T insert(T elem, int index);
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

template <typename T> bool array<T>::empty() const { return msize == 0; }

template <typename T> std::size_t array<T>::size() const { return msize; }

template <typename T> std::size_t array<T>::capacity() const {
  return mcapacity;
}

template <typename T>
void array<T>::print() const {
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

