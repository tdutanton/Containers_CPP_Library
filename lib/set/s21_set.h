#ifndef S21_SET_H
#define S21_SET_H

#include "../red_black_tree.h"

namespace s21 {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RedBlackTree<Key, Key, Key>::iterator;
  using const_iterator = typename RedBlackTree<Key, Key, Key>::const_iterator;
  using size_type = size_t;

  set() : tree_(){};
  set(std::initializer_list<value_type> const& items);
  set(const set& s) : tree_(s.tree_){};
  set(set&& s);
  ~set() = default;
  set& operator=(set&& s);

  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const Key& key);
  bool contains(const Key& key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RedBlackTree<Key, Key, Key> tree_;
};
}  // namespace s21

#include "s21_set.tpp"
#endif