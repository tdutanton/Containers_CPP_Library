#ifndef RED_BLACK_TREE_TPP
#define RED_BLACK_TREE_TPP

#include "red_black_tree.h"

namespace s21 {

/*
*****************************
RebBlackTree constructors
*****************************
*/

template <typename D, typename K, typename V>
RedBlackTree<D, K, V>::RedBlackTree() {
  leaf_ = new Node();
  root_ = leaf_;
};

template <typename D, typename K, typename V>
RedBlackTree<D, K, V>::RedBlackTree(const RedBlackTree& other)
    : RedBlackTree() {
  if (other.root_ != nullptr && !other.root_->is_leaf) {
    this->root_ = copy_tree(other.root_);
  }
};

template <typename D, typename K, typename V>
RedBlackTree<D, K, V>::RedBlackTree(RedBlackTree&& other) {
  if (this->root_ != other.root_) {
    this->root_ = other.root_;
    this->leaf_ = new Node();
    other.root_ = other.leaf_;
  }
};

template <typename D, typename K, typename V>
RedBlackTree<D, K, V>::RedBlackTree(
    std::initializer_list<data_type> const& items)
    : RedBlackTree() {
  for (auto i = items.begin(); i != items.end(); i++) {
    insert_node(*i);
  }
};

template <typename D, typename K, typename V>
RedBlackTree<D, K, V>& RedBlackTree<D, K, V>::operator=(
    const RedBlackTree& other) {
  if (this->root_ != other.root_) {
    this->clear();
    if (other.root_ != nullptr && !other.root_->is_leaf) {
      root_ = copy_tree(other.root_);
    }
  }
  return *this;
}

template <typename D, typename K, typename V>
RedBlackTree<D, K, V>& RedBlackTree<D, K, V>::operator=(RedBlackTree&& other) {
  if (this->root_ != other.root_) {
    this->clear();
    delete this->leaf_;
    this->leaf_ = other.leaf_;
    this->root_ = other.root_;
    other.leaf_ = new Node();
    other.root_ = other.leaf_;
  }
  return *this;
}

template <typename D, typename K, typename V>
RedBlackTree<D, K, V>::~RedBlackTree() {
  clear();
  delete leaf_;
};

/*
*****************************
RebBlackTree private methods
*****************************
*/

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* RedBlackTree<D, K, V>::insert_node(
    const data_type& value) {
  Node* current = this->root_;
  Node* parent = nullptr;
  while (current != nullptr && !current->is_leaf) {
    parent = current;
    if (less(value, current->data)) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  Node* new_node = new Node{leaf_, leaf_, parent, RED, value, 0};
  if (parent != nullptr) {
    if (less(value, parent->data)) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
  } else {
    root_ = new_node;
  }
  balance_insert(new_node);
  return new_node;
};

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::balance_insert(Node* new_node) {
  Node* uncle = nullptr;
  while (new_node != root_ && new_node->parent->color == RED) {
    if (new_node->parent == new_node->parent->parent->left) {
      uncle = new_node->parent->parent->right;
      if (uncle->color == RED) {
        new_node->parent->color = BLACK;
        uncle->color = BLACK;
        new_node->parent->parent->color = RED;
        new_node = new_node->parent->parent;
      } else {
        if (new_node == new_node->parent->right) {
          new_node = new_node->parent;
          left_rotate(new_node);
        }
        new_node->parent->color = BLACK;
        new_node->parent->parent->color = RED;
        right_rotate(new_node->parent->parent);
      }
    } else {
      uncle = new_node->parent->parent->left;
      if (uncle && uncle->color == RED) {
        new_node->parent->color = BLACK;
        uncle->color = BLACK;
        new_node->parent->parent->color = RED;
        new_node = new_node->parent->parent;
      } else {
        if (new_node == new_node->parent->left) {
          new_node = new_node->parent;
          right_rotate(new_node);
        }
        new_node->parent->color = BLACK;
        new_node->parent->parent->color = RED;
        left_rotate(new_node->parent->parent);
      }
    }
  }
  this->root_->color = BLACK;
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::left_rotate(Node* node) {
  Node* temp_node = node->right;
  node->right = temp_node->left;
  if (!temp_node->left->is_leaf) {
    temp_node->left->parent = node;
  }
  if (!temp_node->is_leaf) {
    temp_node->parent = node->parent;
  }
  if (node->parent != nullptr) {
    if (node == node->parent->left) {
      node->parent->left = temp_node;
    } else {
      node->parent->right = temp_node;
    }
  } else {
    root_ = temp_node;
  }
  temp_node->left = node;
  if (!node->is_leaf) {
    node->parent = temp_node;
  }
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::right_rotate(Node* node) {
  Node* temp_node = node->left;
  node->left = temp_node->right;
  if (!temp_node->right->is_leaf) {
    temp_node->right->parent = node;
  }
  if (!temp_node->is_leaf) {
    temp_node->parent = node->parent;
  }
  if (node->parent != nullptr) {
    if (node == node->parent->right) {
      node->parent->right = temp_node;
    } else {
      node->parent->left = temp_node;
    }
  } else {
    root_ = temp_node;
  }
  temp_node->right = node;
  if (!node->is_leaf) {
    node->parent = temp_node;
  }
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* RedBlackTree<D, K, V>::find_node_data(
    const D& value) {
  Node* current = root_;
  while (current != nullptr && !current->is_leaf) {
    if (equal(value, current->data)) {
      return current;
    } else {
      if (less(value, current->data)) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
  }
  return nullptr;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* RedBlackTree<D, K, V>::find_node_key(
    const K& key) {
  Node* current = root_;
  while (current != nullptr && !current->is_leaf) {
    if (equal(key, current->data)) {
      return current;
    } else {
      if (less(key, current->data)) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
  }
  return nullptr;
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::delete_node(Node* removable) {
  Node *x, *y;

  if (removable == nullptr || removable->is_leaf) return;

  if (removable->left->is_leaf || removable->right->is_leaf) {
    y = removable;
  } else {
    y = removable->left;
    while (!y->right->is_leaf) y = y->right;
  }

  if (!y->left->is_leaf) {
    x = y->left;
  } else {
    x = y->right;
  }

  x->parent = y->parent;
  if (y->parent != nullptr) {
    if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }
  } else {
    root_ = x;
  }

  if (y != removable) removable->data = y->data;
  if (y->color == BLACK) balance_remove(x);

  delete y;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* RedBlackTree<D, K, V>::find_max(
    Node* node) {
  Node* max = node;
  Node* right_child = node->right;
  while (right_child != nullptr && !right_child->is_leaf) {
    max = right_child;
    right_child = right_child->right;
  }
  return max;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* RedBlackTree<D, K, V>::find_min(
    Node* node) {
  Node* min = node;
  Node* left_child = node->left;
  while (left_child != nullptr && !left_child->is_leaf) {
    min = left_child;
    left_child = left_child->left;
  }
  return min;
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::balance_remove(Node* node) {
  while (node != root_ && node->color == BLACK) {
    if (node == node->parent->left) {
      Node* brother = node->parent->right;
      if (brother->color == RED) {
        brother->color = BLACK;
        node->parent->color = RED;
        left_rotate(node->parent);
        brother = node->parent->right;
      }
      if (brother->left->color == BLACK && brother->right->color == BLACK) {
        brother->color = RED;
        node = node->parent;
      } else {
        if (brother->right->color == BLACK) {
          brother->left->color = BLACK;
          brother->color = RED;
          right_rotate(brother);
          brother = node->parent->right;
        }
        brother->color = node->parent->color;
        node->parent->color = BLACK;
        brother->right->color = BLACK;
        left_rotate(node->parent);
        node = root_;
      }
    } else {
      Node* brother = node->parent->left;
      if (brother->color == RED) {
        brother->color = BLACK;
        node->parent->color = RED;
        right_rotate(node->parent);
        brother = node->parent->left;
      }
      if (brother->right->color == BLACK && brother->left->color == BLACK) {
        brother->color = RED;
        node = node->parent;
      } else {
        if (brother->left->color == BLACK) {
          brother->right->color = BLACK;
          brother->color = RED;
          left_rotate(brother);
          brother = node->parent->left;
        }
        brother->color = node->parent->color;
        node->parent->color = BLACK;
        brother->left->color = BLACK;
        right_rotate(node->parent);
        node = root_;
      }
    }
  }
  node->color = BLACK;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* RedBlackTree<D, K, V>::copy_tree(
    Node* node) {
  if (node == nullptr || node->is_leaf) {
    return node;
  }

  Node* new_node = new Node(*node);
  new_node->color = node->color;
  new_node->data = node->data;
  new_node->left = copy_tree(node->left);
  new_node->right = copy_tree(node->right);
  if (new_node->left) new_node->left->parent = new_node;
  if (new_node->right) new_node->right->parent = new_node;
  return new_node;
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::less(const K& left_value,
                                 const K& right_value) const {
  return (left_value < right_value);
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::less(const std::pair<K, V>& left_value,
                                 const std::pair<K, V>& right_value) const {
  return (left_value.first < right_value.first);
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::less(const K& left_value,
                                 const std::pair<K, V>& right_value) const {
  return (left_value < right_value.first);
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::equal(const K& left_value,
                                  const K& right_value) const {
  return (left_value == right_value);
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::equal(const std::pair<K, V>& left_value,
                                  const std::pair<K, V>& right_value) const {
  return (left_value.first == right_value.first);
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::equal(const K& left_value,
                                  const std::pair<K, V>& right_value) const {
  return (left_value == right_value.first);
}

/*
*****************************
RebBlackTree public methods
*****************************
*/

template <typename D, typename K, typename V>
D& RedBlackTree<D, K, V>::operator[](const K& key) {
  Node* node = find_node_key(key);
  if (node == nullptr) {
    node = insert_node({key, V()});
  }
  return node->data;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::iterator RedBlackTree<D, K, V>::begin() {
  return iterator(find_min(root_), this);
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::iterator RedBlackTree<D, K, V>::end() {
  return (root_->is_leaf) ? iterator(find_max(root_), this)
                          : iterator(find_max(root_)->right, this);
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::empty() {
  return (root_ == nullptr || root_->is_leaf);
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::size_type RedBlackTree<D, K, V>::size() {
  int size = 0;
  auto iter = begin();
  while (iter.iter_ != nullptr && !iter.iter_->is_leaf) {
    iter++;
    size++;
  }
  return size;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::size_type RedBlackTree<D, K, V>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::clear() {
  while (root_ != nullptr && !root_->is_leaf) {
    delete_node(find_max(root_));
  }
}

template <typename D, typename K, typename V>
std::pair<typename RedBlackTree<D, K, V>::iterator, bool>
RedBlackTree<D, K, V>::insert(const data_type& value) {
  bool inserted;
  iterator iter = this->begin();
  iter.iter_ = find_node_data(value);
  if (iter.iter_ != nullptr) {
    inserted = false;
  } else {
    iter.iter_ = insert_node(value);
    inserted = true;
  }
  std::pair<typename RedBlackTree<D, K, V>::iterator, bool> result{iter,
                                                                   inserted};
  return result;
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::erase(iterator pos) {
  Node* node = find_node_data(pos.iter_->data);
  delete_node(node);
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::erase(const key_type& key) {
  Node* node = find_node_key(key);
  delete_node(node);
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::swap(RedBlackTree<D, K, V>& other) {
  std::swap(root_, other.root_);
  std::swap(leaf_, other.leaf_);
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::merge(RedBlackTree<D, K, V>& other) {
  RedBlackTree<D, K, V> temp(other);
  for (auto iter = temp.begin(); iter != temp.end(); iter++) {
    auto check = insert(*iter);
    if (check.second) {
      other.erase(iter);
    }
  }
}

template <typename D, typename K, typename V>
bool RedBlackTree<D, K, V>::contains(const key_type& key) {
  return (find_node_key(key) != nullptr);
}

template <typename D, typename K, typename V>
template <typename... Args>
s21::vector<std::pair<typename RedBlackTree<D, K, V>::iterator, bool>>
RedBlackTree<D, K, V>::insert_many(Args&&... args) {
  s21::vector<std::pair<typename RedBlackTree<D, K, V>::iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::iterator RedBlackTree<D, K, V>::multi_insert(
    const data_type& value) {
  iterator result(insert_node(value), this);
  return result;
}

/*
*****************************
TreeIterator methods
*****************************
*/

template <typename D, typename K, typename V>
TreeIterator<D, K, V>::TreeIterator() : iter_(nullptr) {}

template <typename D, typename K, typename V>
TreeIterator<D, K, V>::TreeIterator(typename RedBlackTree<D, K, V>::Node* node,
                                    const RedBlackTree<D, K, V>* rbtree_)
    : iter_(node), rbtree_(rbtree_) {}

template <typename D, typename K, typename V>
TreeIterator<D, K, V>& TreeIterator<D, K, V>::operator++() {
  if (!iter_->is_leaf) {
    if (iter_ == rbtree_->find_max(rbtree_->root_)) {
      iter_ = rbtree_->find_max(rbtree_->root_)->right;
    } else
      iter_ = get_next(iter_);
  }
  return *this;
}

template <typename D, typename K, typename V>
TreeIterator<D, K, V>& TreeIterator<D, K, V>::operator++(int) {
  ++(*this);
  return *this;
}

template <typename D, typename K, typename V>
TreeIterator<D, K, V>& TreeIterator<D, K, V>::operator--() {
  if (iter_ == rbtree_->find_max(rbtree_->root_)->right) {
    iter_ = rbtree_->find_max(rbtree_->root_);
  } else if (iter_ != rbtree_->find_min(rbtree_->root_) && !iter_->is_leaf) {
    iter_ = get_prev(iter_);
  }
  return *this;
}

template <typename D, typename K, typename V>
TreeIterator<D, K, V>& TreeIterator<D, K, V>::operator--(int) {
  --(*this);
  return *this;
}

template <typename D, typename K, typename V>
const D& TreeIterator<D, K, V>::operator*() const {
  return iter_->data;
}

template <typename D, typename K, typename V>
const D* TreeIterator<D, K, V>::operator->() const {
  return &(iter_->data);
}

template <typename D, typename K, typename V>
std::pair<const K, V>* TreeIterator<D, K, V>::operator->() {
  return reinterpret_cast<std::pair<const K, V>*>(&(iter_->data));
}

template <typename D, typename K, typename V>
TreeIterator<D, K, V>& TreeIterator<D, K, V>::operator=(
    const TreeIterator& other) {
  if (this != &other) {
    iter_ = other.iter_;
    rbtree_ = other.rbtree_;
  }
  return *this;
}

template <typename D, typename K, typename V>
bool TreeIterator<D, K, V>::operator==(const TreeIterator& other) const {
  return (this->iter_ == other.iter_);
}

template <typename D, typename K, typename V>
bool TreeIterator<D, K, V>::operator!=(const TreeIterator& other) const {
  return (this->iter_ != other.iter_);
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* TreeIterator<D, K, V>::get_next(
    typename RedBlackTree<D, K, V>::Node* current) {
  typename RedBlackTree<D, K, V>::Node* next = nullptr;
  if (current->right != nullptr && !current->right->is_leaf) {
    next = current->right;
    while (next->left != nullptr && !next->left->is_leaf) {
      next = next->left;
    }
  } else {
    typename RedBlackTree<D, K, V>::Node* temp = current;
    next = current->parent;
    while (next != nullptr && !next->is_leaf && next->right == temp) {
      temp = next;
      next = temp->parent;
    }
  }
  return next;
}

template <typename D, typename K, typename V>
typename RedBlackTree<D, K, V>::Node* TreeIterator<D, K, V>::get_prev(
    typename RedBlackTree<D, K, V>::Node* current) {
  typename RedBlackTree<D, K, V>::Node* prev = nullptr;
  if (current->left != nullptr && !current->left->is_leaf) {
    prev = current->left;
    while (prev->right != nullptr && !prev->right->is_leaf) {
      prev = prev->right;
    }
  } else {
    typename RedBlackTree<D, K, V>::Node* temp = current;
    prev = current->parent;
    while (prev != nullptr && !prev->is_leaf && prev->left == temp) {
      temp = prev;
      prev = temp->parent;
    }
  }
  return prev;
}

/*
*****************************
TreeConstIterator methods
*****************************
*/

template <typename D, typename K, typename V>
TreeConstIterator<D, K, V>::TreeConstIterator() : TreeIterator<D, K, V>() {}

template <typename D, typename K, typename V>
TreeConstIterator<D, K, V>::TreeConstIterator(
    const typename RedBlackTree<D, K, V>::Node* node,
    const RedBlackTree<D, K, V>* rbtree_)
    : TreeIterator<D, K, V>(
          const_cast<typename RedBlackTree<D, K, V>::Node*>(node),
          const_cast<RedBlackTree<D, K, V>*>(rbtree_)) {}

/*
*****************************
Print tree methods
*****************************
*/

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::print_node(Node* node) {
  if (node == nullptr || node->is_leaf) {
    printf("\x1b[34m");
    std::cout << "null";
    printf("\x1b[0m");
  } else if (node->color == RED) {
    printf("\x1b[31m");
    std::cout << node->data /* .first */ << " " << node->data /* .second */;
    printf("\x1b[0m");
  } else if (node->color == BLACK) {
    printf("\x1b[34m");
    std::cout << node->data /* .first */ << " " << node->data /* .second */;
    printf("\x1b[0m");
  }
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::print_recursive(Node* root, int space) {
  constexpr int COUNT = 5;
  if (root == nullptr || root->is_leaf) {
    std::cout << "null tree" << std::endl;
    return;
  } else {
    space += COUNT;
    if (root->right != nullptr && !root->right->is_leaf) {
      print_recursive(root->right, space);
    }
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++) std::cout << " ";
    print_node(root);
    std::cout << std::endl;
    if (root->left != nullptr && !root->left->is_leaf) {
      print_recursive(root->left, space);
    }
  }
}

template <typename D, typename K, typename V>
void RedBlackTree<D, K, V>::print_tree() {
  print_recursive(root_, 0);
}
}  // namespace s21

#endif