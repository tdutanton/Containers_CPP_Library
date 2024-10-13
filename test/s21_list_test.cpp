#include "s21_test.h"

TEST(Constructor_list, Default) {
  s21::list<int> data;
  ASSERT_EQ(data.size(), 0);
}

TEST(Constructor_list, Size_n) {
  s21::list<int> data(5);
  std::list<int> data_2(5);
  ASSERT_EQ(data.size(), data_2.size());
  ASSERT_EQ(*data.begin(), *data_2.begin());
}

TEST(Constructor_list, copy) {
  s21::list<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);
  s21::list<int> copy(original);
  ASSERT_EQ(copy.size(), original.size());
  ASSERT_EQ(*(original.begin()), *(copy.begin()));
}

TEST(Constructor_list, move) {
  s21::list<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);
  s21::list<int> moved(std::move(original));
  ASSERT_EQ(moved.size(), 3);
  ASSERT_EQ(original.size(), 0);
}

TEST(Constructor_list, initializer) {
  s21::list<int> list{1, 2, 3, 4};
  std::list<int> list_2{1, 2, 3, 4};
  ASSERT_EQ(list.size(), 4);
  ASSERT_EQ(list.size(), list_2.size());
  ASSERT_EQ(*list.begin(), *list_2.begin());
}

TEST(Method_list, size_empty) {
  s21::list<int> data;
  ASSERT_EQ(data.size(), 0);
  ASSERT_EQ(data.empty(), 1);
}

TEST(Method_list, size_iterators) {
  s21::list<int> l;
  std::list<int> l2;

  l2.push_back(50);
  l2.push_back(20);
  l2.push_back(30);
  l2.push_front(40);

  l.push_back(50);
  l.push_back(20);
  l.push_back(30);
  l.push_front(40);

  ASSERT_EQ(l.size(), 4);
  ASSERT_EQ(l.size(), l2.size());
  ASSERT_EQ(*(--l.end()), *(--l2.end()));
  ASSERT_EQ(*(l.end()--), *(--l2.end()));
  ASSERT_EQ(*(l.begin()), *(l2.begin()));
  ASSERT_EQ(*(l.begin()++), *(++l2.begin()));
  ASSERT_EQ(*(++l.begin()), *(++l2.begin()));
  ASSERT_TRUE(l.begin() == l.begin());
  ASSERT_TRUE(l.begin() != l.end());
  ASSERT_EQ(l.front(), l2.front());
  ASSERT_EQ(l.back(), l2.back());
  ASSERT_ANY_THROW(*l.begin()--);
  ASSERT_EQ((l.back() - 1), (--l2.back()));
  l.erase(l.begin());
  l2.erase(l2.begin());
  ASSERT_EQ(l.size(), 3);
  ASSERT_EQ(l.size(), l2.size());
  ASSERT_EQ(*(l.begin()), *(l2.begin()));
}

TEST(Method_list, max_size) {
  std::list<char> data_std(5);
  s21::list<char> data(5);

  std::list<int> data_std_2(5);
  s21::list<int> data_2(5);

  ASSERT_EQ(data.max_size(), data_std.max_size());
  ASSERT_EQ(data_2.max_size(), data_std_2.max_size());
}

TEST(Method_list, clear) {
  s21::list<int> l;
  std::list<int> l2;

  l2.push_back(50);
  l2.push_back(20);
  l2.push_back(30);
  l2.push_front(40);

  l.push_back(50);
  l.push_back(20);
  l.push_back(30);
  l.push_front(40);

  l.pop_back();
  l2.pop_back();

  ASSERT_EQ(l.size(), 3);
  ASSERT_EQ(*(l.end()--), *(--l2.end()));

  l.pop_front();
  l2.pop_front();

  ASSERT_EQ(l.size(), 2);
  ASSERT_EQ(*(l.end()--), *(--l2.end()));

  l.clear();
  l2.clear();
  ASSERT_EQ(l.size(), 0);
  ASSERT_EQ(l.size(), l2.size());
}

TEST(Method_list, reverse) {
  s21::list<int> list{1, 2, 3, 4};
  std::list<int> list_2{4, 3, 2, 1};

  list.reverse();
  ASSERT_EQ(*(list.begin()), *(list_2.begin()));
  ASSERT_EQ(*(--list.end()), *(--list_2.end()));
}

TEST(Method_list, splice) {
  s21::list<int> list{1, 2, 3, 4};
  s21::list<int> list_2{40, 30, 20, 10};

  list.splice(list.begin(), list_2);

  ASSERT_EQ(list.size(), 8);
  ASSERT_EQ(*(--list.end()), 4);
}

TEST(Method_list, sort) {
  s21::list<int> list{1, -5, 3, 3, 100, 10000, -8};
  std::list<int> list_2{1, -5, 3, 3, 100, 10000, -8};

  list.sort();
  list_2.sort();

  ASSERT_EQ(*(list.begin()), *(list_2.begin()));
  ASSERT_EQ(*(--list.end()), *(--list_2.end()));
}

TEST(Method_list, merge) {
  s21::list<int> list{1, 2, 3, 4};
  s21::list<int> list_2{10, 20, 30};

  std::list<int> list_3{1, 2, 3, 4};
  std::list<int> list_4{10, 20, 30};

  list.merge(list_2);
  list_3.merge(list_4);

  ASSERT_EQ(*(list.begin()), *(list_3.begin()));
  ASSERT_EQ(*(--list.end()), *(--list_3.end()));
}

TEST(Method_list, unique) {
  s21::list<int> list{1, 2, 2, 2, 3, 4, 5, 6, 6, 7};
  std::list<int> list_2{1, 2, 2, 2, 3, 4, 5, 6, 6, 7};

  list.unique();
  list_2.unique();

  ASSERT_EQ(*(list.begin()), *(list_2.begin()));
  ASSERT_EQ(*(--list.end()), *(--list_2.end()));
  ASSERT_EQ(list.size(), list_2.size());
}

TEST(Method_list, insert_many) {
  s21::list<int> list;
  list.insert_many_front(1, 2, 3, 4);
  list.insert_many_back(100);

  ASSERT_EQ(*(list.begin()), 1);
  ASSERT_EQ(*(--list.end()), 100);
  ASSERT_EQ(list.size(), 5);
}