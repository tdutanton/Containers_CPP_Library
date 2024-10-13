#ifndef S211_SET_TPP
#define S211_SET_TPP

#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) : tree_() {
  for (auto iter = items.begin(); iter != items.end(); iter++) {
    tree_.insert(*iter);
  }
}

template <typename Key>
set<Key>::set(set&& s) {
  tree_ = std::move(s.tree_);
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) {
  tree_ = std::move(s.tree_);
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return tree_.end();
}

template <typename Key>
bool set<Key>::empty() {
  return tree_.empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return tree_.size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return tree_.max_size();
}

template <typename Key>
void set<Key>::clear() {
  tree_.clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  return tree_.insert(value);
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
void set<Key>::swap(set& other) {
  tree_.swap(other.tree_);
}

template <typename Key>
void set<Key>::merge(set& other) {
  tree_.merge(other.tree_);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  for (auto iter = tree_.begin(); iter != tree_.end(); iter++) {
    if (*iter == key) {
      return iter;
    }
  }
  return tree_.end();
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  return tree_.contains(key);
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  return tree_.insert_many(std::forward<Args>(args)...);
}

}  // namespace s21

#endif