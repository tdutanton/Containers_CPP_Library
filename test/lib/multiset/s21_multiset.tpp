#ifndef S21_MULTISET_TPP
#define S21_MULTISET_TPP

#include "s21_multiset.h"

namespace s21 {

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : tree_() {
  for (auto iter = items.begin(); iter != items.end(); iter++) {
    tree_.multi_insert(*iter);
  }
}

template <typename Key>
multiset<Key>::multiset(multiset&& ms) {
  tree_ = std::move(ms.tree_);
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& ms) {
  tree_ = std::move(ms.tree_);
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return tree_.end();
}

template <typename Key>
bool multiset<Key>::empty() {
  return tree_.empty();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  return tree_.size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return tree_.max_size();
}

template <typename Key>
void multiset<Key>::clear() {
  tree_.clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  return tree_.multi_insert(value);
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  tree_.swap(other.tree_);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  for (auto iter = other.begin(); iter != other.end(); iter++) {
    insert(*iter);
  }
  other.clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  for (auto iter = tree_.begin(); iter != tree_.end(); iter++) {
    if (*iter == key) {
      return iter;
    }
  }
  return tree_.end();
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) {
  return tree_.contains(key);
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  size_type count = 0;
  for (auto iter = tree_.begin(); iter != tree_.end(); iter++) {
    if (*iter == key) {
      count++;
    }
  }
  return count;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  for (auto iter = tree_.begin(); iter != tree_.end(); iter++) {
    if (*iter >= key) {
      return iter;
    }
  }
  return tree_.end();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  for (auto iter = tree_.begin(); iter != tree_.end(); iter++) {
    if (*iter > key) {
      return iter;
    }
  }
  return tree_.end();
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> result;
  (result.push_back(
       std::make_pair(tree_.multi_insert(std::forward<Args>(args)), true)),
   ...);
  return result;
}
}  // namespace s21
#endif