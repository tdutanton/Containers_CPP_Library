#ifndef S21_LIST_TPP
#define S21_LIST_TPP

#include "s21_list.h"

namespace s21 {

// default constructor
template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

// parameterized constructor, creates the list of size n
template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; i++) {
    push_front(T());
  }
}

// copy constructor
template <typename T>
list<T>::list(const list& l) : list() {
  ListNode_* current = l.head_;
  while (current) {
    push_back(current->data_);
    current = current->next_;
  }
}

// move constructor
template <typename T>
list<T>::list(list&& l) : head_(nullptr), tail_(nullptr), size_(0) {
  swap(l);
}

// initializer list constructor, creates list initizialized using
// std::initializer_list
template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const auto& iter : items) {
    push_back(iter);
  }
}

// destructor
template <typename T>
list<T>::~list() {
  while (head_) {
    ListNode_* temp = head_;
    head_ = head_->next_;
    delete temp;
  }
  tail_ = nullptr;
  size_ = 0;
}

// returns the number of elements
template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

// checks whether the container is empty
template <typename T>
bool list<T>::empty() const noexcept {
  return !static_cast<bool>(size());
}

// create node for list
template <typename T>
list<T>::ListNode_::ListNode_(const T& data)
    : data_(data), next_(nullptr), prev_(nullptr){};

// inserts elements into concrete pos and returns the iterator that points to
// the new element cppreference says "Inserts value before pos"
template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  ListNode_* old_position = pos.iterator_;
  ListNode_* new_element = new ListNode_(value);
  if (empty()) {
    head_ = new_element;
    tail_ = new_element;
  } else if (old_position == tail_->next_) {  // push_back
    tail_->next_ = new_element;
    new_element->prev_ = tail_;
    tail_ = new_element;
  } else {
    new_element->next_ = old_position;
    new_element->prev_ = old_position->prev_;
    if (old_position->prev_)
      old_position->prev_->next_ = new_element;
    else
      head_ = new_element;
    old_position->prev_ = new_element;
  }
  size_++;
  return iterator(new_element, this);
}

// returns an iterator to the beginning
template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return iterator(head_, this);
}

// returns an iterator to the end
template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return iterator(tail_ ? tail_->next_ : nullptr, this);
}

// returns an iterator to the beginning
template <typename T>
typename list<T>::const_iterator list<T>::begin() const noexcept {
  return const_iterator(head_, this);
}

// returns an iterator to the end
template <typename T>
typename list<T>::const_iterator list<T>::end() const noexcept {
  return const_iterator(tail_ ? tail_->next_ : nullptr, this);
}

// adds an element to the end
template <typename T>
void list<T>::push_back(const_reference value) {
  insert(end(), value);
}

// adds an element to the beginning
template <typename T>
void list<T>::push_front(const_reference value) {
  insert(begin(), value);
}

// access the first element
template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return *begin();
}

// access the last element
template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return *(end()--);
}

// returns the maximum possible number of elements
template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  size_type bits = (sizeof(void*) == 4) ? 31 : 63;
  return (static_cast<size_type>(1) << bits) / sizeof(ListNode_);
}

// erases element at pos
template <typename T>
void list<T>::erase(iterator pos) {
  if (empty() || pos == end()) {
    throw std::out_of_range("Error! You can't erase this element");
  }
  ListNode_* delete_position = pos.iterator_;
  if (delete_position->prev_ != nullptr) {
    delete_position->prev_->next_ = delete_position->next_;
  } else {
    head_ = delete_position->next_;
  }
  if (delete_position->next_ != nullptr) {
    delete_position->next_->prev_ = delete_position->prev_;
  } else {
    tail_ = delete_position->prev_;
  }
  delete delete_position;
  size_--;
}

// clears the contents
template <typename T>
void list<T>::clear() noexcept {
  while (!empty()) erase(begin());
}

// removes the last element
template <typename T>
void list<T>::pop_back() {
  erase(--end());
}

// removes the first element
template <typename T>
void list<T>::pop_front() {
  erase(begin());
}

// swaps the contents
template <typename T>
void list<T>::swap(list& other) noexcept {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
}

// reverses the order of the elements
template <typename T>
void list<T>::reverse() noexcept {
  if (size() > 1) {
    iterator left = begin();
    iterator right = --end();
    while (left < right) {
      std::swap(*left, *right);
      ++left;
      --right;
    }
  }
}

// transfers elements from list other starting from pos
template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (!empty()) {
    ListNode_* position = pos.iterator_;
    if (empty()) {
      head_ = other.head_;
      tail_ = other.tail_;
    } else if (position == tail_->next_) {
      tail_->next_ = other.head_;
      other.head_->prev_ = tail_;
      tail_ = other.tail_;
    } else {
      other.tail_->next_ = position;
      other.tail_->prev_ = position->prev_;
      if (position->prev_)
        position->prev_->next_ = other.head_;
      else
        head_ = other.head_;
      position->prev_ = other.tail_;
    }
    size_ += other.size();
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }
}

// sorts the elements
template <typename T>
void list<T>::sort() {
  if (!empty()) {
    bool swap = true;
    while (swap) {
      swap = false;
      ListNode_* cur = head_;
      while (cur->next_) {
        if (cur->data_ > cur->next_->data_) {
          std::swap(cur->data_, cur->next_->data_);
          swap = true;
        }
        cur = cur->next_;
      }
    }
  }
}

// merges two sorted lists
template <typename T>
void list<T>::merge(list& other) {
  list<T> tmp_1(*this);
  list<T> tmp_2(other);
  tmp_1.sort();
  tmp_2.sort();
  if (*this != other && tmp_1 == *this && tmp_2 == other) {
    splice(begin(), other);
    sort();
  }
  size_ += other.size();
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <typename T>
bool list<T>::operator==(const list<T>& other) {
  bool result = false;
  if (size() == other.size()) {
    result = true;
    iterator first = begin();
    iterator second = other.begin();
    while (result && first != end()) {
      if (*first != *second)
        result = false;
      else {
        ++first;
        ++second;
      }
    }
  }
  return result;
}

template <typename T>
bool list<T>::operator!=(const list<T>& other) {
  return !(*this == other);
}

// removes consecutive duplicate elements
template <typename T>
void list<T>::unique() {
  if (!empty()) {
    for (iterator it = begin(); it != end(); ++it) {
      iterator next = it;
      ++next;
      while (next != end() && *it == *next) {
        erase(next);
        next = it;
        ++next;
      }
    }
  }
}

// bonus part

// Inserts new elements into the container directly before pos
template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator it = pos;
  for (const auto& elem : {args...}) {
    it = insert(it, elem);
    if (it.iterator_ != tail_->next_) it++;
  }
  return it;
}

// Inserts new elements into the container directly before pos
template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  insert_many(end(), std::forward<value_type>(args)...);
}

// Appends new elements to the top of the container
template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  insert_many(begin(), std::forward<value_type>(args)...);
}

}  // namespace s21

#endif