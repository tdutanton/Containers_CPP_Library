#include "s21_test.h"

TEST(Constructor_array, _default) {
  s21::array<int, 4> a;
  ASSERT_EQ(a.size(), 4);
}

TEST(Constructor_array, init_list) {
  s21::array<int, 4> a{1, 2, 3};
  std::array<int, 4> b{1, 2, 3};
  ASSERT_EQ(a.size(), b.size());
  ASSERT_EQ(a[3], b[3]);
}

TEST(Constructor_array, copy_array) {
  s21::array<int, 4> a{1, 2, 3};
  s21::array<int, 4> b(a);
  std::array<int, 4> a_origin{1, 2, 3};
  std::array<int, 4> b_origin(a_origin);

  ASSERT_EQ(b.size(), b_origin.size());
  ASSERT_EQ(b[3], b_origin[3]);
}

TEST(Constructor_array, move_array) {
  s21::array<int, 4> a{1, 2, 3};
  s21::array<int, 4> moved(std::move(a));
  ASSERT_EQ(moved.size(), 4);
  ASSERT_EQ(a.size(), 0);
}

TEST(Iterators_array, begin_end_empy) {
  s21::array<int, 4> a{1, 2, 3};
  std::array<int, 4> a_origin{1, 2, 3};

  ASSERT_EQ(*a.begin(), *a_origin.begin());
  ASSERT_EQ(*(a.begin() + 1), *(a_origin.begin() + 1));
  ASSERT_EQ(*(a.end() - 1), *(a_origin.end() - 1));
  EXPECT_FALSE(a.empty());
}

TEST(Methods_array, max_size) {
  std::array<char, 5> data_std;
  s21::array<char, 5> data;

  std::array<int, 5> data_std_2;
  s21::array<int, 5> data_2;

  ASSERT_EQ(data.max_size(), data_std.max_size());
  ASSERT_EQ(data_2.max_size(), data_std_2.max_size());
}

TEST(Methods_array, swap) {
  std::array<int, 4> a{1, 2, 3, 4};
  std::array<int, 4> b{5, 6, 7, 8};

  s21::array<int, 4> c{1, 2, 3, 4};
  s21::array<int, 4> d{5, 6, 7, 8};

  ASSERT_EQ(*a.begin(), *c.begin());
  ASSERT_EQ(*(a.end() - 1), *(c.end() - 1));

  a.swap(b);
  c.swap(d);

  ASSERT_EQ(*(a.begin() + 1), *(c.begin() + 1));
  ASSERT_EQ(*(a.end() - 1), *(c.end() - 1));
}

TEST(Operator_array, assignment_operator_for_moving_object) {
  s21::array<int, 4> data;
  data = s21::array<int, 4>{1, 2, 34, 5};

  ASSERT_EQ(data[0], 1);
  ASSERT_EQ(data[1], 2);
  ASSERT_EQ(data[2], 34);
  ASSERT_EQ(data[3], 5);
}

TEST(Methods_array, at_front_end_data) {
  std::array<int, 4> a{1, 2, 3, 4};
  s21::array<int, 4> b{1, 2, 3, 4};

  a.at(2) = 100;
  b.at(2) = 100;
  ASSERT_EQ(*a.begin(), *b.begin());
  ASSERT_EQ(a[2], b[2]);
  ASSERT_EQ(a.front(), b.front());
  ASSERT_EQ(a.back(), b.back());
  ASSERT_EQ(*a.data(), *b.data());
}

TEST(Methods_array, fill) {
  std::array<int, 4> a;
  s21::array<int, 4> b;

  a.fill(1000);
  b.fill(1000);
  ASSERT_EQ(*a.begin(), *b.begin());
  ASSERT_EQ(a[2], b[2]);
  ASSERT_EQ(a.front(), b.front());
  ASSERT_EQ(a.back(), b.back());
  ASSERT_EQ(*a.data(), *b.data());
}