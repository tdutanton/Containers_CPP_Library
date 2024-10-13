#ifndef S21_VECTOR_H
#define S21_VECTOR_H

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

  vector();                      // default constructor
  explicit vector(size_type n);  // parameterized constructor
  explicit vector(std::initializer_list<value_type> const
                      &items);  // initializer list constructor
  vector(const vector &v);      // copy constructor
  vector(vector &&v) noexcept;  // move constructor
  ~vector();                    // destructor

  vector &operator=(
      vector &&v) noexcept;  // assignment operator overload for moving object
  reference operator[](size_type pos);  // access specified element

  reference at(size_type pos);  // access specified element with bounds checking

  iterator data() noexcept;  // direct access to the underlying array
  void swap(
      vector &other) noexcept;  // swaps the contents (noexcept - since c++17)
  size_type capacity()
      const noexcept;  // returns the number of elements that can be held in
                       // currently allocated storage
  void reserve(
      size_type size);   // allocate storage of size elements and copies current
                         // array elements to a newely allocated array
  void shrink_to_fit();  // reduces memory usage by freeing unused memory
  const_reference back() const;   // access the last element
  const_reference front() const;  // access the first element
  size_type max_size() const noexcept;
  size_type size() const noexcept;  // returns the number of elements
  void pop_back();                  // removes the last element

  void clear();               // clears the contents
  iterator begin() noexcept;  // returns an iterator to the beginning
  iterator end() noexcept;    // returns an iterator to the end
  iterator insert(
      iterator pos,
      const_reference value);  // inserts elements into concrete pos and returns
                               // the iterator that points to the new element
  void erase(iterator pos);    // erases element at pos
  void push_back(const_reference value);  // adds an element to the end
  bool empty() const noexcept;  // checks whether the container is empty

  // additional
  const_iterator begin()
      const noexcept;  // returns a const iterator to the beginning
  const_iterator end() const noexcept;  // returns a const iterator to the end

  // bonus part
  template <typename... Args>
  iterator insert_many(const_iterator pos,
                       Args &&...args);  // Inserts new elements into the
                                         // container directly before pos

  template <typename... Args>
  void insert_many_back(
      Args &&...args);  // Appends new elements to the end of the container

 private:
  T *data_;
  size_type capacity_;
  size_type size_;
};

}  // namespace s21

#include "s21_vector.tpp"

#endif

//   T& reference;
//   const T& const_reference;
//   T* iterator;
//   const T* const_iterator;