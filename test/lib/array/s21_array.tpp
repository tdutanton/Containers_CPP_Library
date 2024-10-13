#ifndef S21_ARRAY_TPP
#define S21_ARRAY_TPP

#include "s21_array.h"

namespace s21 {

// default constructor
template <typename T, size_t N>
array<T, N>::array() {
  size_type bits = (sizeof(void*) == 4) ? 31 : 63;
  if (N > (static_cast<size_type>(1) << bits) / sizeof(value_type) - 1 ||
      N > std::numeric_limits<std::size_t>::max())
    throw std::out_of_range(
        "Error! Number of elements bigger than maximum available number of "
        "elements");
  size_ = N;
}

// initializer list constructor, creates array initizialized using
// std::initializer_list
template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) : array() {
  size_t indx{0};
  for (const auto& i : items) {
    if (indx < items.size()) {
      array_[indx] = i;
      indx++;
    }
  }
  for (; indx < N; indx++) {
    array_[indx] = T();
  }
}

// copy constructor
template <typename T, size_t N>
array<T, N>::array(const array& a) : array() {
  size_ = a.size_;
  for (size_t i = 0; i < a.size_; i++) {
    array_[i] = a.array_[i];
  }
}

// move constructor
template <typename T, size_t N>
array<T, N>::array(array&& a) : array() {
  size_ = a.size_;
  for (size_t i = 0; i < a.size_; i++) {
    array_[i] = std::move(a.array_[i]);
  }
  a.size_ = 0;
}

// destructor
template <typename T, size_t N>
array<T, N>::~array() = default;

// assignment operator overload for moving object
template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array&& a) noexcept {
  if (this != &a) {
    size_ = a.size_;
    for (size_t i = 0; i < a.size_; i++) {
      array_[i] = std::move(a.array_[i]);
    }
    a.size_ = 0;
  }
  return *this;
}

// returns an iterator to the beginning
template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return (empty() ? end() : array_);
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return (empty() ? end() : array_);
}

// returns an iterator to the end
template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return (array_ + size());
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return (array_ + size());
}

// checks whether the container is empty
template <typename T, size_t N>
constexpr bool array<T, N>::empty() const noexcept {
  return !static_cast<bool>(size());
}

// returns the number of elements
template <typename T, size_t N>
constexpr typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return size_;
}

// access specified element
template <typename T, size_t N>
constexpr typename array<T, N>::reference array<T, N>::operator[](
    size_type pos) {
  return array_[pos];
}

// returns the maximum possible number of elements
template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return size();
}

// swaps the contents
template <typename T, size_t N>
void array<T, N>::swap(array& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(array_, other.array_);
}

// access specified element with bounds checking
template <typename T, size_t N>
constexpr typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_)
    throw std::out_of_range("Error! Position of value is out of range");
  return array_[pos];
}

// access the first element
template <typename T, size_t N>
constexpr typename array<T, N>::const_reference array<T, N>::front() const {
  return *begin();
}

// access the last element
template <typename T, size_t N>
constexpr typename array<T, N>::const_reference array<T, N>::back() const {
  return *(end() - 1);
}

// direct access to the underlying array
template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return (size() == 0) ? nullptr : array_;
}

// assigns the given value value to all elements in the container
template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (auto& i : array_) {
    i = value;
  }
}

}  // namespace s21

#endif