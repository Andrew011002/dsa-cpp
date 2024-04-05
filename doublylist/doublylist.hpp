#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

template <typename T> class node {
public:
  T key;
  std::shared_ptr<node<T>> prev;
  std::shared_ptr<node<T>> next;
  node(T k);
};

template <typename T>
node<T>::node(T k) : key(k), prev(nullptr), next(nullptr) {}

template <typename T> class iterator {
  std::shared_ptr<node<T>> curr_ptr;

public:
  iterator(std::shared_ptr<node<T>> ptr);
  iterator<T> &operator++();
  iterator<T> operator++(int) const;
  iterator<T> &operator--();
  iterator<T> operator--(int) const;
  bool operator==(const iterator<T> &other) const;
  bool operator!=(const iterator<T> &other) const;
  T operator*() const;
};

template <typename T>
iterator<T>::iterator(std::shared_ptr<node<T>> ptr) : curr_ptr(ptr) {}

template <typename T> iterator<T> &iterator<T>::operator++() {
  if (curr_ptr != nullptr) {
    curr_ptr = curr_ptr->next;
  }
  return *this;
}

template <typename T> iterator<T> iterator<T>::operator++(int) const {
  return iterator<T>(curr_ptr->next);
}

template <typename T> iterator<T> &iterator<T>::operator--() {
  if (curr_ptr != nullptr) {
    curr_ptr = curr_ptr->prev;
  }
  return *this;
}

template <typename T> iterator<T> iterator<T>::operator--(int) const {
  return iterator<T>(curr_ptr->prev);
}

template <typename T>
bool iterator<T>::operator==(const iterator<T> &other) const {
  return curr_ptr == other.curr_ptr;
}

template <typename T>
bool iterator<T>::operator!=(const iterator<T> &other) const {
  return curr_ptr.get() != other.curr_ptr.get();
}

template <typename T> T iterator<T>::operator*() const {
  if (curr_ptr != nullptr) {
    return curr_ptr->key;
  }
  return T();
}

template <typename T> class doublylist {
  std::shared_ptr<node<T>> m_head;
  std::shared_ptr<node<T>> m_tail;
  std::size_t m_length;
  bool out_of_bounds(int index) const;
  std::uint32_t to_index(int index) const;

public:
  doublylist();
  T get(int index) const;
  void update(int index, T key);
  void append(T key);
  void insert(int index, T key);
  void remove(T index);
  bool contains(T key) const;
  std::uint32_t count(T key) const;
  int find(T key) const;
  std::size_t length() const;
  iterator<T> begin() const;
  iterator<T> end() const;
  std::string repr() const;
  void print() const;
};

template <typename T> bool doublylist<T>::out_of_bounds(int index) const {
  if (index < 0) {
    return std::abs(index) > m_length;
  }
  return index < m_length;
}

template <typename T> std::uint32_t doublylist<T>::to_index(int index) const {
  if (index < 0) {
    return index + m_length;
  }
  return index;
}

template <typename T>
doublylist<T>::doublylist() : m_head(nullptr), m_tail(nullptr), m_length(0) {}

template <typename T> T doublylist<T>::get(int index) const {
  if (out_of_bounds(index)) {
    throw new std::exception();
  }
  index = to_index(index);
  std::shared_ptr<node<T>> curr_ptr = m_head;
  for (int i = 0; i < index; i++) {
    curr_ptr = curr_ptr->next;
  }
  return curr_ptr->key;
}

template <typename T> void doublylist<T>::append(T key) {
  if (m_head == nullptr) {
    m_head = std::make_shared<node<T>>(key);
  } else if (m_tail == nullptr) {
    m_tail = std::make_shared<node<T>>(key);
    m_head->next = m_tail;
    m_tail->prev = m_head;
  } else {
    m_tail->next = std::make_shared<node<T>>(key);
    m_tail->next->prev = m_tail;
    m_tail = m_tail->next;
  }
  m_length++;
}

template <typename T> iterator<T> doublylist<T>::begin() const {
  return iterator<T>(m_head);
}

template <typename T> iterator<T> doublylist<T>::end() const {
  return iterator<T>(m_tail->next);
}
