#ifndef S21_MAP_H
#define S21_MAP_H

#include "../red_black_tree.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RedBlackTree<std::pair<Key, T>, Key, T>::iterator;
  using const_iterator =
      typename RedBlackTree<std::pair<Key, T>, Key, T>::const_iterator;
  using size_type = size_t;

  map() : tree_(){};
  map(std::initializer_list<value_type> const& items);
  map(const map& m) : tree_(m.tree_){};
  map(map&& m);
  ~map() = default;
  map& operator=(map&& m);

  T& at(const Key& key);
  T& operator[](const Key& key);

  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  bool contains(const Key& key);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RedBlackTree<std::pair<Key, T>, Key, T> tree_;
};
}  // namespace s21

#include "s21_map.tpp"
#endif