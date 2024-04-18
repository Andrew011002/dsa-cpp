#include <array>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

const std::size_t DEFAULT_CAPACITY = 7;
const std::size_t MAX_LIST_LENGTH = 5;

template <typename T, typename U> class node {
public:
  T key;
  std::optional<U> value;
  std::shared_ptr<node<T, U>> next;
  node();
  node(T key);
  node(T key, U value);
  node(T key, U value, std::size_t length);
};

template <typename T, typename U> node<T, U>::node() {}
template <typename T, typename U> node<T, U>::node(T key) : key(key) {}
template <typename T, typename U>
node<T, U>::node(T key, U value) : key(key), value(value) {}

template <typename T, typename U> class linkedlist {
  typedef std::shared_ptr<node<T, U>> node_ptr_t;
  node_ptr_t m_head;
  node_ptr_t m_tail;
  std::size_t m_length;

public:
  linkedlist();
  std::optional<U> get(T key) const;
  void push(T key);
  void push(T key, U value);
  void update(T key, U value);
  void remove(T key);
  bool contains(T key) const;
  std::size_t length() const;
  void print() const;
};

template <typename T, typename U>
linkedlist<T, U>::linkedlist() : m_length(0) {}

template <typename T, typename U>
std::optional<U> linkedlist<T, U>::get(T key) const {
  node_ptr_t node = m_head;
  while (node && node->key != key) {
    node = node->next;
  }
  return node->value;
};

template <typename T, typename U> void linkedlist<T, U>::push(T key) {
  if (!m_head) {
    m_head = std::make_shared<node<T, U>>(key);
  } else if (!m_tail) {
    m_tail = std::make_shared<node<T, U>>(key);
    m_head->next = m_tail;
  } else {
    m_tail->next = std::make_shared<node<T, U>>(key);
    m_tail = m_tail->next;
  }
  m_length++;
}

template <typename T, typename U> void linkedlist<T, U>::push(T key, U value) {
  if (!m_head) {
    m_head = std::make_shared<node<T, U>>(key, value);
  } else if (!m_tail) {
    m_tail = std::make_shared<node<T, U>>(key, value);
    m_head->next = m_tail;
  } else {
    m_tail->next = std::make_shared<node<T, U>>(key, value);
    m_tail = m_tail->next;
  }
  m_length++;
}

template <typename T, typename U>
void linkedlist<T, U>::update(T key, U value) {
  node_ptr_t node = m_head;
  while (node && node->key != key) {
    node = node->next;
  }
  node->value = value;
}

template <typename T, typename U> void linkedlist<T, U>::remove(T key) {
  node_ptr_t prev_node;
  node_ptr_t curr_node = m_head;
  while (curr_node && curr_node->key != key) {
    prev_node = curr_node;
    curr_node = curr_node->next;
  }
  if (curr_node == m_head) {
    m_head = m_head->next;
  } else if (curr_node == m_tail) {
    m_tail = prev_node;
    m_tail->next = nullptr;
  } else {
    prev_node->next = curr_node->next;
  }
  m_length--;
}

template <typename T, typename U> bool linkedlist<T, U>::contains(T key) const {
  node_ptr_t node = m_head;
  while (node) {
    if (node->key == key) {
      return true;
    }
    node = node->next;
  }
  return false;
}

template <typename T, typename U> std::size_t linkedlist<T, U>::length() const {
  return m_length;
}

template <typename T, typename U> void linkedlist<T, U>::print() const {
  node_ptr_t node = m_head;
  std::cout << "[";
  for (int i = 0; i < m_length; i++) {
    std::cout << node->key << ": ";
    if (node->value) {
      std::cout << node->value.value();
    } else {
      std::cout << "null";
    }
    if (i != m_length - 1) {
      std::cout << ", ";
    }
    node = node->next;
  }
  std::cout << "]\n";
}

template <typename T, typename U> class map {
  typedef std::unique_ptr<linkedlist<T, U>> list_ptr_t;
  std::array<list_ptr_t, DEFAULT_CAPACITY> m_array;
  std::size_t m_size;
  std::size_t m_capacity;
  std::hash<T> m_hash;

public:
  map();
  void add(T key);
  void add(T key, U value);
  void update(T key, U value);
  void remove(T key);
  bool contains(T key) const;
  std::optional<U> get(T key) const;
  std::size_t hash(T key) const;
  void resize();
  std::size_t size() const;
  std::size_t capacity() const;
  std::string string() const;
  void print() const;
};

template <typename T, typename U>
map<T, U>::map() : m_size(0), m_capacity(DEFAULT_CAPACITY) {}

template <typename T, typename U>
std::optional<U> map<T, U>::get(T key) const {}

template <typename T, typename U> void map<T, U>::add(T key, U value) {}

template <typename T, typename U> void map<T, U>::add(T key) {}

template <typename T, typename U> void map<T, U>::update(T key, U value) {}

template <typename T, typename U> bool map<T, U>::contains(T key) const {
  std::size_t index = hash(key);
  list_ptr_t list_ptr = m_array[index];
  while (list_ptr->length() > 0) {
    if (list_ptr->contains(key)) {
      return true;
    }
    index = (index + 1) % m_capacity;
    list_ptr = m_array[index];
  }
  return false;
}

template <typename T, typename U> std::size_t map<T, U>::hash(T key) const {
  return m_hash(key) % m_capacity;
}

template <typename T, typename U> void map<T, U>::resize() {}

template <typename T, typename U> std::size_t map<T, U>::size() const {
  return m_size;
}

template <typename T, typename U> std::size_t map<T, U>::capacity() const {
  return m_capacity;
}

template <typename T, typename U> std::string map<T, U>::string() const {}

template <typename T, typename U> void map<T, U>::print() const {}
