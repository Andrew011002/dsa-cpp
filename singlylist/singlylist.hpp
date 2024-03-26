#include <iostream>
#include <memory>

template <typename T> class node {
public:
  node(T k) : key(k) {}
  T key;
  std::shared_ptr<node<T>> next;
};

template <typename T> class singlylist {
  std::shared_ptr<node<T>> m_head;
  std::shared_ptr<node<T>> m_tail;
  std::size_t m_length;
  void remove_helper(T key);

public:
  singlylist();
  void add(T key);
  void insert(T key, int index);
  void remove(T key);
  bool contains(T key) const;
  int length() const;
  void print() const;
};

template <typename T>
singlylist<T>::singlylist() : m_head(nullptr), m_tail(nullptr), m_length(0) {}

template <typename T> void singlylist<T>::add(T key) {
  if (m_length == 0) {
    m_head = std::make_shared<node<T>>(key);
  } else if (m_length == 1) {
    m_tail = std::make_shared<node<T>>(key);
    m_head->next = m_tail;
  } else {
    m_tail->next = std::make_shared<node<T>>(key);
    m_tail = m_tail->next;
  }
  m_length++;
}

template <typename T> void singlylist<T>::remove_helper(T key) {
  if (m_length == 1) {
    m_head.reset();
  }
  node<T> *curr_ptr = m_head.get();
  node<T> *prev_ptr = nullptr;
  while (*curr_ptr != key) {
    prev_ptr = curr_ptr;
    curr_ptr = curr_ptr->next.get();
  }
  if
}

template <typename T> void singlylist<T>::remove(T key) {}

template <typename T> void singlylist<T>::insert(T key, int index) {}

template <typename T> bool singlylist<T>::contains(T key) const {
  node<T> *ptr = m_head.get();
  for (int i = 0; i < m_length; i++) {
    if (*ptr == key) {
      return true;
    }
    ptr = ptr->next.get();
  }
  return false;
}

template <typename T> int singlylist<T>::length() const { return m_length; }

template <typename T> void singlylist<T>::print() const {
  node<T> *ptr = m_head.get();
  std::cout << "[";
  for (int i = 0; i < m_length; i++) {
    std::cout << ptr->key;
    if (i < m_length - 1) {
      std::cout << ", ";
    }
    ptr = ptr->next.get();
  }
  std::cout << "]\n";
}
