#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>

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
  std::size_t length;
};

template <typename T, typename U> node<T, U>::node() {}
template <typename T, typename U> node<T, U>::node(T key) : key(key) {}
template <typename T, typename U>
node<T, U>::node(T key, U value) : key(key), value(value) {}
template <typename T, typename U>
node<T, U>::node(T key, U value, std::size_t length)
    : key(key), value(value), length(length) {}

template <typename T, typename U> class map {
  std::array<node<T, U>, DEFAULT_CAPACITY> m_nodes;
  std::size_t m_size;
  std::size_t m_capacity;

public:
  void add(T key);
  void add(T key, U value);
  void update(T key, U value);
  void remove(T key);
  bool contains(T key) const;
  std::optional<U> get(T key) const;
  std::uint32_t hash(T key) const;
  std::size_t length() const;
  std::size_t capacity() const;
  std::string string() const;
  void print() const;
};
