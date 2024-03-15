#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>

const std::size_t CAPACITY = 0;

template <typename T> class vector {
  std::size_t m_size;
  std::size_t m_capacity;
  std::unique_ptr<T> m_ptr;

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
  m_ptr = std::make_unique(new T[m_capacity]);
}

template <typename T> vector<T>::vector() : vector<T>(CAPACITY) {}

template <typename T> void vector<T>::modify(int index, T element) {
  *(m_ptr + index) = element;
}

template <typename T> T vector<T>::get(int index) const {
  return m_ptr.get() + index;
}

template <typename T> void vector<T>::append(T element) {
  *(m_ptr + m_size++) = element;
}

template <typename T> bool vector<T>::empty() const { return m_size == 0; }

template <typename T> bool vector<T>::full() const {
  return m_size == m_capacity;
}

template <typename T> std::size_t vector<T>::size() const { return m_size; }

template <typename T> std::size_t vector<T>::capacity() const {
  return m_capacity;
}

template <typename T> void vector<T>::print() const {
  T *ptr = m_ptr.get();
  std::cout << "[";
  for (int i = 0; i < m_size; i++) {
    std::cout << *ptr++;
    if (i < m_size - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]\n";
}
