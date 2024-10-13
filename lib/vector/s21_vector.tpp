#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

#include "s21_vector.h"

namespace s21 {

// default constructor
template <typename T>
vector<T>::vector() : data_(nullptr), capacity_(0), size_(0) {}

// parameterized constructor
template <typename T>
vector<T>::vector(size_type n) {
  data_ = new T[n]();
  size_ = n;
  capacity_ = n;
}

// initializer list constructor
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  data_ = new value_type[items.size()]();
  size_ = items.size();
  capacity_ = items.size();
  std::copy(items.begin(), items.end(), data_);
}

// copy constructor
template <typename T>
vector<T>::vector(const vector &v) : capacity_(v.capacity_) {
  size_ = v.size_;
  data_ = new value_type[v.size_]();
  for (size_type i = 0; i < v.size_; i++) {
    data_[i] = v.data_[i];
  }
}

// move constructor
template <typename T>
vector<T>::vector(vector &&v) noexcept : capacity_(v.capacity_) {
  size_ = v.size_;
  data_ = std::move(v.data_);
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

// destructor
template <typename T>
vector<T>::~vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

// assignment operator overload for moving object
template <typename T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
  this->swap(v);
  delete[] v.data_;
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
  return *this;
}

// access specified element
template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

// access specified element with bounds checking
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_)
    throw std::out_of_range("Error! Position of value is out of range");
  return data_[pos];
}

// direct access to the underlying array
template <typename T>
typename vector<T>::iterator vector<T>::data() noexcept {
  return (size() == 0) ? nullptr : data_;
}

// swaps the contents
template <typename T>
void vector<T>::swap(vector &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// returns the number of elements that can be held in currently allocated
// storage
template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

// clears the contents
template <typename T>
void vector<T>::clear() {
  delete[] data_;
  size_ = 0;
  data_ = nullptr;
}

// returns an iterator to the beginning
template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return empty() ? end() : data_;
}

// returns a const iterator to the beginning
template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept {
  return empty() ? end() : data_;
}

// returns an iterator to the end
template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return data_ + size();
}

// returns a const iterator to the end
template <typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept {
  return data_ + size();
}

// allocate storage of size elements and copies current array elements to a
// newely allocated array
template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size())
    throw std::length_error("Size of reserving storage is unavailable");
  if (size > capacity_) {
    T *data_tmp = new T[size]();
    std::move(data_, data_ + this->size_, data_tmp);
    delete[] data_;
    data_ = data_tmp;
    capacity_ = size;
  }
}

// reduces memory usage by freeing unused memory
template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    T *data_tmp = new T[size_];
    std::move(data_, data_ + size_, data_tmp);
    delete[] data_;
    data_ = data_tmp;
    capacity_ = size_;
  }
}

// inserts elements into concrete pos and returns the iterator that points to
// the new element
template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (this->size_ == capacity_) {
    reserve(capacity_ == 0                               ? 1
            : (this->max_size() - capacity_) > capacity_ ? capacity_ * 2
                                                         : this->max_size());
  }
  iterator new_pos = begin() + index;
  for (size_type i = size_; i > index; i--) {
    data_[i] = data_[i - 1];
  }
  *new_pos = value;
  size_++;
  return new_pos;
}

// erases element at pos
template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - begin();
  for (size_t i = index; i < size_ - 1; i++) {
    data_[i] = data_[i + 1];
  }
  size_--;
}

// access the last element
template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return *(end() - 1);
}

// returns the maximum possible number of elements
template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  size_type bits = (sizeof(void *) == 4) ? 31 : 63;
  return (static_cast<size_type>(1) << bits) / sizeof(value_type) - 1;
}

// removes the last element
template <typename T>
void vector<T>::pop_back() {
  erase(end() - 1);
}

// returns the number of elements
template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

// access the first element
template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return *begin();
}

// checks whether the container is empty
template <typename T>
bool vector<T>::empty() const noexcept {
  return !static_cast<bool>(size());
}

// adds an element to the end
template <typename T>
void vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

// bonus part

// Inserts new elements into the container directly before pos
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  iterator it = (iterator)pos;
  for (const auto &elem : {args...}) {
    it = insert(it, elem);
    ++it;
  }
  return it;
}

// Inserts new elements into the container directly before pos
template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(end(), std::forward<T>(args)...);
}

}  // namespace s21

#endif