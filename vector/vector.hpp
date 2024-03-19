#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

const std::size_t DEFAULT_CAPACITY = 4;

template <typename T> class vector {
  std::size_t m_size;
  std::size_t m_capacity;
  std::unique_ptr<T[]> m_ptr;

public:
  vector();
  vector(std::uint32_t capacity);
  T get(int index) const;
  void modify(int index, T element);
  void append(T element);
  void remove(T element);
  void remove(T element, std::uint32_t n);
  void removeall(T element);
  void insert(int index, T element);
  bool contains(T element) const;
  std::uint32_t count(T element) const;
  int find(T element) const;
  int find(T element, int start) const;
  void clear();
  std::uint32_t toindex(int index) const;
  bool outofbounds(int index) const;
  void resize();
  bool empty() const;
  bool full() const;
  std::size_t size() const;
  std::size_t capacity() const;
  void print() const;
};

template <typename T> vector<T>::vector(std::uint32_t capacity) {
  m_size = 0;
  m_capacity = capacity;
  m_ptr = std::make_unique<T[]>(capacity);
}

template <typename T> vector<T>::vector() : vector<T>(0) {}

template <typename T> void vector<T>::modify(int index, T element) {
  if (outofbounds(index)) {
    throw new std::exception();
  }
  *(m_ptr.get() + toindex(index)) = element;
}

template <typename T> T vector<T>::get(int index) const {
  if (outofbounds(index)) {
    throw new std::exception();
  }
  return *(m_ptr.get() + toindex(index));
}

template <typename T> void vector<T>::append(T element) {
  if (full()) {
    resize();
  }
  *(m_ptr.get() + m_size++) = element;
}

template <typename T> void vector<T>::insert(int index, T element) {
  if (index != m_size && outofbounds(index)) {
    throw new std::exception();
  }
  if (full()) {
    resize();
  }
  index = toindex(index);
  if (index == m_size) {
    append(element);
    return;
  }
  for (int i = index; i < m_size + 1; i++) {
    T tmp = *(m_ptr.get() + i);
    *(m_ptr.get() + i) = element;
    element = tmp;
  }
  m_size++;
}

template <typename T> bool vector<T>::contains(T element) const {
  for (int i = 0; i < m_size; i++) {
    if (*(m_ptr.get() + i) == element) {
      return true;
    }
  }
  return false;
}

template <typename T> std::uint32_t vector<T>::toindex(int index) const {
  if (index < 0) {
    return index + m_size;
  }
  return index;
}

template <typename T> bool vector<T>::outofbounds(int index) const {
  if (index < 0) {
    return std::abs(index) > m_size;
  }
  return index >= m_size;
}

template <typename T> void vector<T>::resize() {
  m_capacity = std::max(m_capacity * 2, DEFAULT_CAPACITY);
  std::unique_ptr<T[]> old_ptr = std::move(m_ptr);
  std::size_t old_size = m_size;
  m_ptr = std::make_unique<T[]>(m_capacity);
  m_size = 0;
  for (int i = 0; i < old_size; i++) {
    append(*(old_ptr.get() + i));
  }
};

template <typename T> bool vector<T>::empty() const { return m_size == 0; }

template <typename T> bool vector<T>::full() const {
  return m_size == m_capacity;
}

template <typename T> std::size_t vector<T>::size() const { return m_size; }

template <typename T> std::size_t vector<T>::capacity() const {
  return m_capacity;
}

template <typename T> void vector<T>::print() const {
  std::cout << "[";
  for (int i = 0; i < m_size; i++) {
    std::cout << *(m_ptr.get() + i);
    if (i < m_size - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]\n";
}
