#ifndef S21_LIST_ITERATORS_TPP
#define S21_LIST_ITERATORS_TPP

#include "s21_list.h"

namespace s21 {

template <typename T>
ListIterator<T>::ListIterator() {
  iterator_ = nullptr;
}

template <typename T>
ListIterator<T>::ListIterator(
    const typename list<T>::ListNode_ *list_element_ptr,
    const list<T> *list_ptr_)
    : iterator_(list_element_ptr), list_ptr_(list_ptr_) {}

template <typename T>
ListIterator<T>::ListIterator(typename list<T>::ListNode_ *list_element_ptr,
                              const list<T> *list_ptr_)
    : iterator_(list_element_ptr), list_ptr_(list_ptr_) {}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator &list_original_element,
                              const list<T> *list_ptr_)
    : iterator_(list_original_element.iterator_), list_ptr_(list_ptr_) {}

template <typename T>
ListConstIterator<T>::ListConstIterator(
    const typename list<T>::ListNode_ *list_element_ptr,
    const list<T> *list_ptr_)
    : ListIterator<T>(
          const_cast<typename list<T>::ListNode_ *>(list_element_ptr),
          list_ptr_) {}

template <typename T>
typename list<T>::reference ListIterator<T>::operator*() {
  if (iterator_ == nullptr) {
    throw std::out_of_range("Error - Invalid pointer");
  }
  return iterator_->data_;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator++() {
  iterator_ = iterator_->next_;
  return *this;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator++(int) {
  iterator_ = iterator_->next_;
  return *this;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator--() {
  if (iterator_ == list_ptr_->head_) {
    throw std::out_of_range("Error - Decrementing out of range");
  } else if (iterator_ == nullptr)
    iterator_ = list_ptr_->tail_;
  else
    iterator_ = iterator_->prev_;
  return *this;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator--(int) {
  if (iterator_ == list_ptr_->head_) {
    throw std::out_of_range("Error - Decrementing out of range");
  } else if (iterator_ == nullptr)
    iterator_ = list_ptr_->tail_;
  else
    iterator_ = iterator_->prev_;
  return *this;
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator &other) {
  return iterator_ == other.iterator_;
}

template <typename T>
bool ListIterator<T>::operator!=(const ListIterator &other) {
  return iterator_ != other.iterator_;
}

template <typename T>
bool ListIterator<T>::operator>(const ListIterator &other) {
  return iterator_ > other.iterator_;
}

template <typename T>
bool ListIterator<T>::operator<(const ListIterator &other) {
  return iterator_ < other.iterator_;
}

// ConstListIterator
template <typename T>
const typename list<T>::const_reference ListConstIterator<T>::operator*()
    const {
  if (this->iterator_ == nullptr) {
    throw std::out_of_range("Error - Invalid pointer");
  }
  return this->iterator_->data_;
}

}  // namespace s21

#endif