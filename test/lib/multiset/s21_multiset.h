#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../red_black_tree.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RedBlackTree<Key, Key, Key>::iterator;
  using const_iterator = typename RedBlackTree<Key, Key, Key>::const_iterator;
  using size_type = size_t;

  multiset() : tree_(){};
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms) : tree_(ms.tree_){};
  multiset(multiset&& ms);
  ~multiset() = default;
  multiset& operator=(multiset&& ms);

  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RedBlackTree<Key, Key, Key> tree_;
};
}  // namespace s21
#include "s21_multiset.tpp"
#endif