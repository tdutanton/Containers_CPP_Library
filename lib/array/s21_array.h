#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <cstddef>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

  array();  // default constructor, creates empty array
  array(std::initializer_list<value_type> const
            &items);      // initializer list constructor, creates array
                          // initizialized using std::initializer_list
  array(const array &a);  // copy constructor
  array(array &&a);       // move constructor
  ~array();               // destructor

  array<T, N> &operator=(
      array &&a) noexcept;  // assignment operator overload for moving object

  iterator begin() noexcept;  // returns an iterator to the beginning
  const_iterator begin() const noexcept;
  iterator end() noexcept;  // returns an iterator to the end
  const_iterator end() const noexcept;
  iterator data() noexcept;  // direct access to the underlying array
  constexpr bool empty()
      const noexcept;  // checks whether the container is empty
  constexpr size_type size() const noexcept;  // returns the number of elements
  size_type max_size()
      const noexcept;  // returns the maximum possible number of elements
  constexpr reference operator[](size_type pos);  // access specified element
  void swap(array &other) noexcept;               // swaps the contents
  constexpr reference at(
      size_type pos);  // access specified element with bounds checking
  constexpr const_reference front() const;  // access the first element
  constexpr const_reference back() const;   // access the last element
  void fill(const_reference value);  // assigns the given value value to all
                                     // elements in the container

 private:
  value_type array_[N];
  size_type size_;
};

}  // namespace s21

#include "s21_array.tpp"

#endif