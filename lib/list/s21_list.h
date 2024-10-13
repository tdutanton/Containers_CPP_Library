#ifndef S21_LIST_H
#define S21_LIST_H

namespace s21 {

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
class list {
  friend ListIterator<T>;
  friend ListConstIterator<T>;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  list();   // default constructor
  ~list();  // destructor
  explicit list(
      size_type n);     // parameterized constructor, creates the list of size n
  list(const list& l);  // copy constructor
  list(list&& l);       // move constructor
  list(std::initializer_list<value_type> const&
           items);  // initializer list constructor, creates list initizialized
                    // using std::initializer_list

  size_type size() const noexcept;  // returns the number of elements
  iterator insert(
      iterator pos,
      const_reference value);  // inserts elements into concrete pos and returns
                               // the iterator that points to the new element
  iterator begin() noexcept;   // returns an iterator to the beginning
  iterator end() noexcept;     // returns an iterator to the end
  const_iterator begin()
      const noexcept;                   // returns an iterator to the beginning
  const_iterator end() const noexcept;  // returns an iterator to the end
  void push_back(const_reference value);   // adds an element to the end
  void push_front(const_reference value);  // adds an element to the end
  void pop_back();                         // removes the last element
  void pop_front();                        // removes the first element
  bool empty() const noexcept;    // checks whether the container is empty
  const_reference front() const;  // access the first element
  const_reference back() const;   // access the last element
  size_type max_size() const noexcept;
  void clear() noexcept;     // clears the contents
  void erase(iterator pos);  // erases element at pos
  void swap(
      list& other) noexcept;  // swaps the contents (noexcept - since c++17)
  void reverse() noexcept;    // reverses the order of the elements
  void splice(
      const_iterator pos,
      list& other);  // transfers elements from list other starting from pos
  void sort();       // sorts the elements
  void merge(list& other);  // merges two sorted lists
  void unique();            // removes consecutive duplicate elements

  // bonus part
  template <typename... Args>
  iterator insert_many(const_iterator pos,
                       Args&&... args);  // Inserts new elements into the
                                         // container directly before pos
  template <typename... Args>
  void insert_many_back(
      Args&&... args);  // Appends new elements to the end of the container
  template <typename... Args>
  void insert_many_front(
      Args&&... args);  // Appends new elements to the top of the container

  // additionals
  bool operator==(const list& other);
  bool operator!=(const list& other);

 private:
  struct ListNode_ {
    T data_;
    ListNode_* next_;
    ListNode_* prev_;
    explicit ListNode_(const T& data);
  };

  ListNode_* head_;  // first elem
  ListNode_* tail_;  // last elem
  size_type size_;   // size
};

// internal class ListIterator<T> defines the type for iterating through the
// container
template <typename T>
class ListIterator {
  friend list<T>;

 public:
  ListIterator();
  explicit ListIterator(const typename list<T>::ListNode_* list_element_ptr,
                        const list<T>* list_ptr_);
  explicit ListIterator(typename list<T>::ListNode_* list_element_ptr,
                        const list<T>* list_ptr_);
  ListIterator(std::nullptr_t) : iterator_(nullptr){};
  ListIterator(const ListIterator& list_original_element,
               const list<T>* list_ptr_);
  typename list<T>::reference operator*();
  ListIterator& operator++();     // prefix
  ListIterator& operator++(int);  // postfix
  ListIterator& operator--();     // prefix
  ListIterator& operator--(int);  /// postfix
  bool operator<(const ListIterator& other);
  bool operator>(const ListIterator& other);
  bool operator==(const ListIterator& other);
  bool operator!=(const ListIterator& other);

 protected:
  typename list<T>::ListNode_* iterator_;
  const list<T>* list_ptr_;
};

// internal class ListConstIterator<T> defines the constant type for iterating
// through the container
template <typename T>
class ListConstIterator : public ListIterator<T> {
  friend list<T>;

 public:
  ListConstIterator() : ListIterator<T>() {}
  explicit ListConstIterator(
      const typename list<T>::ListNode_* list_element_ptr,
      const list<T>* list_ptr_);
  ListConstIterator(std::nullptr_t) : ListIterator<T>(nullptr) {}
  ListConstIterator(const ListIterator<T>& other) : ListIterator<T>(other) {}
  const typename list<T>::const_reference operator*() const;
  const typename list<T>::ListNode_* operator->() const {
    return this->iterator_;
  }
};

}  // namespace s21

#include "s21_list.tpp"
#include "s21_list_iterators.tpp"

#endif