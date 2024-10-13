#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

#include "vector/s21_vector.h"

namespace s21 {

template <typename D, typename K, typename V>
class TreeIterator;

template <typename D, typename K, typename V>
class TreeConstIterator;

template <typename D, typename K, typename V>
class RedBlackTree {
 public:
  friend class TreeIterator<D, K, V>;
  friend class TreeConstIterator<D, K, V>;

  using data_type = D;
  using key_type = K;
  using value_type = V;
  using reference = data_type &;
  using const_reference = const data_type &;
  using iterator = TreeIterator<D, K, V>;
  using const_iterator = TreeConstIterator<D, K, V>;
  using size_type = size_t;

  RedBlackTree();
  RedBlackTree(const RedBlackTree &other);
  RedBlackTree(RedBlackTree &&other);
  RedBlackTree(std::initializer_list<data_type> const &items);
  RedBlackTree &operator=(const RedBlackTree &other);
  reference operator[](const K &key);
  RedBlackTree &operator=(RedBlackTree &&other);
  ~RedBlackTree();

  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const data_type &value);
  void erase(iterator pos);
  void erase(const key_type &key);
  void swap(RedBlackTree &other);
  void merge(RedBlackTree &other);
  bool contains(const key_type &key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  iterator multi_insert(const data_type &value);

  void print_tree();

 protected:
  enum Color { RED, BLACK };

  struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    int color = BLACK;
    data_type data;
    bool is_leaf = true;
  };

  Node *insert_node(const data_type &value);
  void left_rotate(Node *node);
  void right_rotate(Node *node);
  void balance_insert(Node *node);
  void delete_node(Node *node);
  Node *find_node_data(const D &value);
  Node *find_node_key(const K &key);
  void balance_remove(Node *node);
  static Node *find_max(Node *node);
  static Node *find_min(Node *node);
  Node *copy_tree(Node *node);
  void print_node(Node *node);
  void print_recursive(Node *root, int space);

  bool less(const K &left_value, const K &right_value) const;
  bool less(const std::pair<K, V> &left_value,
            const std::pair<K, V> &right_value) const;
  bool less(const K &left_value, const std::pair<K, V> &right_value) const;
  bool equal(const K &left_value, const K &right_value) const;
  bool equal(const std::pair<K, V> &left_value,
             const std::pair<K, V> &right_value) const;
  bool equal(const K &left_value, const std::pair<K, V> &right_value) const;

  Node *leaf_;
  Node *root_;
};

template <typename D, typename K, typename V>
class TreeIterator {
 public:
  friend RedBlackTree<D, K, V>;

  TreeIterator();
  TreeIterator(const TreeIterator<D, K, V> &other)
      : iter_(other.iter_), rbtree_(other.rbtree_){};
  TreeIterator(typename RedBlackTree<D, K, V>::Node *node,
               const RedBlackTree<D, K, V> *rbtree_);
  ~TreeIterator() = default;
  TreeIterator &operator++();
  TreeIterator &operator++(int);
  TreeIterator &operator--();
  TreeIterator &operator--(int);
  const D &operator*() const;
  const D *operator->() const;
  std::pair<const K, V> *operator->();
  TreeIterator &operator=(const TreeIterator &other);
  bool operator==(const TreeIterator &other) const;
  bool operator!=(const TreeIterator &other) const;

 protected:
  typename RedBlackTree<D, K, V>::Node *get_next(
      typename RedBlackTree<D, K, V>::Node *current);
  typename RedBlackTree<D, K, V>::Node *get_prev(
      typename RedBlackTree<D, K, V>::Node *current);

  typename RedBlackTree<D, K, V>::Node *iter_;
  const RedBlackTree<D, K, V> *rbtree_;
};

template <typename D, typename K, typename V>
class TreeConstIterator : public TreeIterator<D, K, V> {
 public:
  friend RedBlackTree<D, K, V>;

  TreeConstIterator();
  TreeConstIterator(const typename RedBlackTree<D, K, V>::Node *node,
                    const RedBlackTree<D, K, V> *rbtree_);
  TreeConstIterator(const TreeIterator<D, K, V> &other)
      : TreeIterator<D, K, V>(other){};
  ~TreeConstIterator() = default;
};

}  // namespace s21

#include "red_black_tree.tpp"

#endif