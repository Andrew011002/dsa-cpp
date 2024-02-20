#include <cstdio>

template <typename T> class Array {
  T *arrptr;
  T *iptr;
  std::size_t msize;
  std::size_t mcapacity;

public:
  Array();
  Array(std::size_t capacity);
  T get(int index) const;
  void modify(int index, T elem);
  T add(T elem);
  void remove(T elem);
  T insert(T elem, int index);
  std::size_t size() const;
  std::size_t capacity() const;
  void print() const;
};

template <typename T>
Array<T>::Array() : arrptr(new T[10]), iptr(arrptr), msize(0), mcapacity(10) {}

template <typename T>
Array<T>::Array(std::size_t capacity)
    : arrptr(new T[capacity]), iptr(arrptr), msize(0), mcapacity(capacity) {}

template <typename T>
Array<T>::get(const int index) const {

}
