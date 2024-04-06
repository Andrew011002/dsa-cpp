#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

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
  iterator<T> operator++(int);
  iterator<T> &operator--();
  iterator<T> operator--(int);
  bool operator==(const iterator<T> &other) const;
  bool operator!=(const iterator<T> &other) const;
  T operator*() const;
  std::shared_ptr<node<T>> operator->() const;
};

template <typename T>
iterator<T>::iterator(std::shared_ptr<node<T>> ptr) : curr_ptr(ptr) {}

template <typename T> iterator<T> &iterator<T>::operator++() {
  if (curr_ptr != nullptr) {
    curr_ptr = curr_ptr->next;
  }
  return *this;
}

template <typename T> iterator<T> iterator<T>::operator++(int) {
  iterator<T> temp = *this;
  if (curr_ptr != nullptr) {
    curr_ptr = curr_ptr->next;
  }
  return temp;
}

template <typename T> iterator<T> &iterator<T>::operator--() {
  if (curr_ptr != nullptr) {
    curr_ptr = curr_ptr->prev;
  }
  return *this;
}

template <typename T> iterator<T> iterator<T>::operator--(int) {
  iterator<T> temp = *this;
  if (curr_ptr != nullptr) {
    curr_ptr = curr_ptr->prev;
  }
  return temp;
}

template <typename T>
bool iterator<T>::operator==(const iterator<T> &other) const {
  return curr_ptr == other.curr_ptr;
}

template <typename T>
bool iterator<T>::operator!=(const iterator<T> &other) const {
  return curr_ptr != other.curr_ptr;
}

template <typename T> T iterator<T>::operator*() const {
  if (curr_ptr != nullptr) {
    return curr_ptr->key;
  }
  return T();
}

template <typename T> std::shared_ptr<node<T>> iterator<T>::operator->() const {
  return curr_ptr;
}

template <typename T> class doublylist {
  std::shared_ptr<node<T>> m_head;
  std::shared_ptr<node<T>> m_tail;
  std::size_t m_length;
  bool out_of_bounds(int index) const;
  std::uint32_t to_index(int index) const;
  void remove_helper(T key);

public:
  doublylist();
  T get(int index) const;
  void update(int index, T key);
  void append(T key);
  void insert(int index, T key);
  void remove(T key, std::uint32_t n = 1);
  void remove_all(T key);
  bool contains(T key) const;
  std::uint32_t count(T key) const;
  int find(T key, int start = 0) const;
  iterator<T> begin() const;
  iterator<T> end() const;
  std::size_t length() const;
  std::string string() const;
  void print() const;
  std::ostream &operator<<(std::ostream &os) const;
};

template <typename T> bool doublylist<T>::out_of_bounds(int index) const {
  if (index < 0) {
    return std::abs(index) > m_length;
  }
  return index >= m_length;
}

template <typename T> std::uint32_t doublylist<T>::to_index(int index) const {
  if (index < 0) {
    return index + m_length;
  }
  return index;
}

template <typename T> void doublylist<T>::remove_helper(T key) {
  std::shared_ptr<node<T>> curr_ptr = m_head;
  for (int i = 0; i < m_length; ++i) {
    if (curr_ptr->key == key) {
      break;
    }
    curr_ptr = curr_ptr->next;
  }
  if (curr_ptr == m_head) {
    m_head = m_head->next;
  } else if (curr_ptr == m_tail) {
    m_tail = m_tail->prev;
  } else {
    curr_ptr->prev->next = curr_ptr->next;
    curr_ptr->next->prev = curr_ptr->prev;
  }
  m_length--;
}

template <typename T>
doublylist<T>::doublylist() : m_head(nullptr), m_tail(nullptr), m_length(0) {}

template <typename T> T doublylist<T>::get(int index) const {
  if (out_of_bounds(index)) {
    throw new std::exception();
  }
  index = to_index(index);
  std::shared_ptr<node<T>> curr_ptr;
  if (m_length - 1 - index < index) {
    curr_ptr = m_tail;
    for (int i = m_length - 1; i > index; --i) {
      curr_ptr = curr_ptr->prev;
    }

  } else {
    curr_ptr = m_head;
    for (int i = 0; i < index; ++i) {
      curr_ptr = curr_ptr->next;
    }
  }
  return curr_ptr->key;
}

template <typename T> void doublylist<T>::update(int index, T key) {
  if (out_of_bounds(index)) {
    throw new std::exception();
  }
  index = to_index(index);
  std::shared_ptr<node<T>> curr_ptr;
  if (m_length - 1 - index < index) {
    curr_ptr = m_tail;
    for (int i = m_length - 1; i > index; --i) {
      curr_ptr = curr_ptr->prev;
    }

  } else {
    curr_ptr = m_head;
    for (int i = 0; i < index; ++i) {
      curr_ptr = curr_ptr->next;
    }
  }
  curr_ptr->key = key;
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

template <typename T> void doublylist<T>::insert(int index, T key) {
  if (std::abs(index) > m_length && out_of_bounds(index)) {
    throw new std::exception();
  }
  index = to_index(index);
  if (index == 0) {
    m_head->prev = std::make_shared<node<T>>(key);
    m_head->prev->next = m_head;
    m_head = m_head->prev;

  } else if (index == m_length) {
    m_tail->next = std::make_shared<node<T>>(key);
    m_tail->next->prev = m_tail;
    m_tail = m_tail->next;

  } else {
    std::shared_ptr<node<T>> curr_ptr;
    std::shared_ptr<node<T>> new_node_ptr = std::make_shared<node<T>>(key);

    if (m_length - 1 - index < index) {
      curr_ptr = m_tail;
      for (int i = m_length - 1; i > index; --i) {
        curr_ptr = curr_ptr->prev;
      }

    } else {
      curr_ptr = m_head;
      for (int i = 0; i < index; ++i) {
        curr_ptr = curr_ptr->next;
      }
    }
    new_node_ptr->prev = curr_ptr->prev;
    new_node_ptr->next = curr_ptr;
    new_node_ptr->prev->next = new_node_ptr;
    curr_ptr->prev = new_node_ptr;
  }
  m_length++;
}

template <typename T> void doublylist<T>::remove(T key, std::uint32_t n) {
  if (count(key) < n) {
    throw new std::exception();
  }
  for (int i = 0; i < n; ++i) {
    remove_helper(key);
  }
}

template <typename T> void doublylist<T>::remove_all(T key) {
  std::uint32_t n;
  if (n = count(key); n < 1) {
    throw new std::exception();
  }
  for (int i = 0; i < n; ++i) {
    remove_helper(key);
  }
}

template <typename T> bool doublylist<T>::contains(T key) const {
  std::shared_ptr<node<T>> curr_ptr = m_head;
  for (int i = 0; i < m_length; ++i) {
    if (curr_ptr->key == key) {
      return true;
    }
    curr_ptr = curr_ptr->next;
  }
  return false;
}

template <typename T> std::uint32_t doublylist<T>::count(T key) const {
  std::shared_ptr<node<T>> curr_ptr = m_head;
  std::uint32_t n = 0;
  for (int i = 0; i < m_length; ++i) {
    if (curr_ptr->key == key) {
      n++;
    }
    curr_ptr = curr_ptr->next;
  }
  return n;
}

template <typename T> int doublylist<T>::find(T key, int start) const {
  if (out_of_bounds(start)) {
    throw new std::exception();
  }
  start = to_index(start);
  std::shared_ptr<node<T>> curr_ptr = m_head;
  for (int i = 0; i < m_length; ++i) {
    if (curr_ptr->key == key && i >= start) {
      return i;
    }
    curr_ptr = curr_ptr->next;
  }
  return -1;
}

template <typename T> iterator<T> doublylist<T>::begin() const {
  return iterator<T>(m_head);
}

template <typename T> iterator<T> doublylist<T>::end() const {
  return iterator<T>(m_tail->next);
}

template <typename T> std::size_t doublylist<T>::length() const {
  return m_length;
}

template <typename T> std::string doublylist<T>::string() const {
  std::string s = "[";
  std::shared_ptr<node<T>> curr_ptr = m_head;
  for (int i = 0; i < m_length; ++i) {
    s.append(std::to_string(curr_ptr->key));
    if (i < m_length - 1) {
      s.append(" ");
    }
    curr_ptr = curr_ptr->next;
  }
  s.append("]");
  return s;
}

template <typename T>
std::ostream &doublylist<T>::operator<<(std::ostream &os) const {
  os << string();
  return os;
}

template <typename T> void doublylist<T>::print() const {
  *this << std::cout << "\n";
}
