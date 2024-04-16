#include <cstddef>
#include <memory>
#include <optional>

template <typename T, typename U> class node {
public:
  T key;
  std::optional<U> value;
  std::shared_ptr<node<T, U>> next;
  node();
  node(T key);
  node(T key, U value);
  std::size_t length;
};

template <typename T, typename U> node<T, U>::node() {}
template <typename T, typename U> node<T, U>::node(T key) : key(key) {}
template <typename T, typename U>
node<T, U>::node(T key, U value) : key(key), value(value) {}
