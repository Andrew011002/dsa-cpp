#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

template <typename T> class node {
public:
  node(T k) : key(k) {}
  T key;
  std::shared_ptr<node<T>> next;
};

template <typename T> class iter {
  std::shared_ptr<node<T>> curr_ptr;

public:
  iter(std::shared_ptr<node<T>> ptr) : curr_ptr(ptr) {}

  iter &operator++() {
    if (curr_ptr != nullptr) {
      curr_ptr = curr_ptr->next;
    }
    return *this;
  }

  bool operator!=(const iter &other) const {
    return curr_ptr.get() != other.curr_ptr.get();
  }

  T operator*() const { return curr_ptr->key; }
};

template <typename T> class singlylist {
  std::shared_ptr<node<T>> m_head;
  std::shared_ptr<node<T>> m_tail;
  std::size_t m_length;
  void remove_helper(T key);
  bool out_of_bounds(int index) const;
  std::uint32_t to_index(int index) const;

public:
  singlylist();
  void update(T key, int index);
  T get(int index) const;
  void add(T key);
  void insert(T key, int index);
  void remove(T key);
  void remove(T key, std::uint32_t n);
  void remove_all(T key);
  bool contains(T key) const;
  std::uint32_t count(T key) const;
  int find(T key, int index) const;
  int find(T key) const;
  std::size_t length() const;
  void print() const;
  iter<T> begin() const;
  iter<T> end() const;
};

template <typename T>
singlylist<T>::singlylist() : m_head(nullptr), m_tail(nullptr), m_length(0) {}

template <typename T> bool singlylist<T>::out_of_bounds(int index) const {
  if (index < 0) {
    return std::abs(index) > m_length;
  }
  return index >= m_length;
}

template <typename T> std::uint32_t singlylist<T>::to_index(int index) const {
  if (index < 0) {
    return m_length + index;
  }
  return index;
}
template <typename T> void singlylist<T>::update(T key, int index) {
  if (out_of_bounds(index)) {
    throw new std::exception();
  }
  std::shared_ptr<node<T>> ptr = m_head;
  for (int i = 0; i < index; i++) {
    ptr = ptr->next;
  }
  ptr->key = key;
}

template <typename T> T singlylist<T>::get(int index) const {
  if (out_of_bounds(index)) {
    throw new std::exception();
  }
  std::shared_ptr<node<T>> ptr = m_head;
  for (int i = 0; i < index; i++) {
    ptr = ptr->next;
  }
  return ptr->key;
}

template <typename T> void singlylist<T>::add(T key) {
  if (m_head == nullptr) {
    m_head = std::make_shared<node<T>>(key);
    m_tail = m_head;
  } else {
    m_tail->next = std::make_shared<node<T>>(key);
    m_tail = m_tail->next;
  }
  m_length++;
}

template <typename T> void singlylist<T>::remove_helper(T key) {
  std::shared_ptr<node<T>> curr_ptr = m_head;
  std::shared_ptr<node<T>> prev_ptr;

  while (curr_ptr->key != key) {
    prev_ptr = curr_ptr;
    curr_ptr = curr_ptr->next;
  }

  if (curr_ptr.get() == m_head.get() && curr_ptr.get() == m_tail.get()) {
    m_head.reset();
    m_tail.reset();

  } else if (curr_ptr.get() == m_head.get()) {
    m_head = m_head->next;

  } else if (curr_ptr.get() == m_tail.get()) {
    m_tail = prev_ptr;
    m_tail->next.reset();

  } else {
    prev_ptr->next = curr_ptr->next;
  }
  m_length--;
}

template <typename T> void singlylist<T>::remove(T key) {
  if (contains(key) == false) {
    throw new std::exception();
  }
  remove_helper(key);
}

template <typename T> void singlylist<T>::remove(T key, std::uint32_t n) {
  std::uint32_t amount = count(key);
  if (amount < n) {
    throw new std::exception();
  }
  for (int i = 0; i < n; i++) {
    remove_helper(key);
  }
}

template <typename T> void singlylist<T>::remove_all(T key) {
  std::uint32_t amount = count(key);
  for (int i = 0; i < amount; i++) {
    remove_helper(key);
  }
}

template <typename T> void singlylist<T>::insert(T key, int index) {
  if (out_of_bounds(index) && index > m_length) {
    throw new std::exception();
  }

  index = to_index(index);
  std::shared_ptr<node<T>> curr_ptr = m_head;
  std::shared_ptr<node<T>> prev_ptr;

  for (int i = 0; i < index; i++) {
    prev_ptr = curr_ptr;
    curr_ptr = curr_ptr->next;
  }

  std::shared_ptr<node<T>> new_node = std::make_shared<node<T>>(key);
  if (index == 0) {
    new_node->next = m_head;
    m_head = new_node;

  } else if (index == m_length) {
    m_tail->next = new_node;
    m_tail = new_node;

  } else {
    new_node->next = curr_ptr;
    prev_ptr->next = new_node;
  }
  m_length++;
}

template <typename T> bool singlylist<T>::contains(T key) const {
  node<T> *ptr = m_head.get();
  for (int i = 0; i < m_length; i++) {
    if (ptr->key == key) {
      return true;
    }
    ptr = ptr->next.get();
  }
  return false;
}

template <typename T> std::uint32_t singlylist<T>::count(T key) const {
  std::uint32_t amount = 0;
  std::shared_ptr<node<T>> ptr = m_head;
  for (int i = 0; i < m_length; i++) {
    if (ptr->key == key) {
      amount++;
    }
    ptr = ptr->next;
  }
  return amount;
}

template <typename T> int singlylist<T>::find(T key, int start) const {
  if (out_of_bounds(start)) {
    throw new std::exception();
  }
  start = to_index(start);
  std::shared_ptr<node<T>> ptr = m_head;
  for (int i = 0; i < m_length; i++) {
    if (ptr->key == key && i >= start) {
      return i;
    }
    ptr = ptr->next;
  }
  return -1;
}

template <typename T> int singlylist<T>::find(T key) const {
  return find(key, 0);
}

template <typename T> iter<T> singlylist<T>::begin() const {
  return iter<T>(m_head);
}

template <typename T> iter<T> singlylist<T>::end() const {
  return iter<T>(m_tail->next);
}

template <typename T> std::size_t singlylist<T>::length() const {
  return m_length;
}

template <typename T> void singlylist<T>::print() const {
  std::shared_ptr<node<T>> ptr = m_head;
  std::cout << "[";
  for (int i = 0; i < m_length; i++) {
    std::cout << ptr->key;
    if (i < m_length - 1) {
      std::cout << ", ";
    }
    ptr = ptr->next;
  }
  std::cout << "]\n";
}
