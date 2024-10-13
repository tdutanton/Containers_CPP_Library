#ifndef S21_MAP_TPP
#define S21_MAP_TPP

#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) {
  for (auto iter = items.begin(); iter != items.end(); iter++) {
    tree_.insert(*iter);
  }
}

template <typename Key, typename T>
map<Key, T>::map(map&& m) {
  tree_ = std::move(m.tree_);
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& m) {
  tree_ = std::move(m.tree_);
  return *this;
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  if (!tree_.contains(key)) throw std::out_of_range("map::at - Key not found");
  return tree_[key].second;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return tree_[key].second;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return tree_.begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return tree_.end();
}

template <typename Key, typename T>
bool map<Key, T>::empty() {
  return tree_.empty();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return tree_.size();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return tree_.max_size();
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  tree_.clear();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  return tree_.insert(value);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  return tree_.insert({key, obj});
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  auto result = tree_.insert({key, obj});
  if (!result.second) {
    tree_[key].second = obj;
  }
  return result;
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  tree_.merge(other.tree_);
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  return tree_.contains(key);
}

template <typename Key, typename T>
template <typename... Args>
s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  return tree_.insert_many(std::forward<Args>(args)...);
}

}  // namespace s21

#endif