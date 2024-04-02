#include <cstddef>
#include <cstdint>
#include <memory>

template <typename T> class node {
public:
  T key;
  std::shared_ptr<node<T>> prev;
  std::shared_ptr<node<T>> next;
};

template <typename T> class iterator {};

template <typename T> class doublylist {
  std::shared_ptr<node<T>> m_head;
  std::shared_ptr<node<T>> m_tail;
  std::size_t m_length;
  bool out_of_bounds(int index) const;
  std::uint32_t to_index(int index) const;

public:
  doublylist();
  T get() const;
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
