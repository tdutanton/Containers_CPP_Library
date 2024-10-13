#include "s21_test.h"

TEST(Constructor_vector, Default) {
  s21::vector<int> data;
  ASSERT_EQ(data.data(), nullptr);
  ASSERT_EQ(data.capacity(), 0);
  ASSERT_EQ(data.size(), 0);
}

TEST(Constructor_vector, Size) {
  s21::vector<int> data(10);
  ASSERT_EQ(data.size(), 10);
}

TEST(Constructor_vector, Copy_vector) {
  s21::vector<int> data_f{2, 3, 4};
  s21::vector<int> data_res(data_f);

  ASSERT_EQ(data_res[0], 2);
  ASSERT_EQ(data_res[1], 3);
  ASSERT_EQ(data_res[2], 4);
}

TEST(Constructor_vector, move_vector) {
  s21::vector<int> data_f{2, 3, 4};
  s21::vector<int> data_res(std::move(data_f));

  ASSERT_EQ(data_res[0], 2);
  ASSERT_EQ(data_res[1], 3);
  ASSERT_EQ(data_res[2], 4);

  ASSERT_EQ(data_f.data(), nullptr);
  ASSERT_EQ(data_f.size(), 0);
}

TEST(Constructor_vector, initialize_list) {
  s21::vector<int> data{1, 2, 3};
  ASSERT_EQ(data[0], 1);
  ASSERT_EQ(data[1], 2);
  ASSERT_EQ(data[2], 3);
}

TEST(Operator, assignment_operator_for_moving_object) {
  s21::vector<int> data;
  data = s21::vector<int>{1, 2, 34, 5};

  ASSERT_EQ(data[0], 1);
  ASSERT_EQ(data[1], 2);
  ASSERT_EQ(data[2], 34);
  ASSERT_EQ(data[3], 5);
}

TEST(Method, element_access_front) {
  DEFUALT_V;

  ASSERT_EQ(data.front(), 1);
}

TEST(Method, element_access_back) {
  DEFUALT_V;

  ASSERT_EQ(data.back(), 4);
}

TEST(Method, at) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};

  ASSERT_EQ(data.at(1), 2);
  ASSERT_EQ(data.at(1), data_std.at(1));
}

TEST(Method, at_bad) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};

  EXPECT_ANY_THROW(data.at(4));
  EXPECT_ANY_THROW(data.at(6));
}

TEST(Method, modifier_clear) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};

  data.clear();
  data_std.clear();

  ASSERT_EQ(data.size(), 0);
  ASSERT_EQ(data.size(), data_std.size());
  ASSERT_EQ(data.capacity(), data_std.capacity());
}

TEST(Iterators, iterator_begin) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};

  ASSERT_EQ(*data.begin(), *data_std.begin());
  ASSERT_EQ(*data.begin(), 1);
}

TEST(Iterators, iterator_end) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};

  ASSERT_EQ(*(data.end() - 1), *(data_std.end() - 1));
  ASSERT_EQ(*(data.end() - 2), 3);
  ASSERT_EQ(*(data_std.end() - 2), 3);
}

TEST(Method, max_size) {
  std::vector<char> data_std(5);
  s21::vector<char> data(5);

  std::vector<int> data_std_2(5);
  s21::vector<int> data_2(5);

  ASSERT_EQ(data.max_size(), data_std.max_size());
  ASSERT_EQ(data_2.max_size(), data_std_2.max_size());
}

TEST(Method, reserve_good) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};

  data.reserve(6);
  data_std.reserve(6);
  ASSERT_EQ(data.capacity(), data_std.capacity());
  ASSERT_EQ(data.capacity(), 6);
}

TEST(Method, reserve_bad) {
  DEFUALT_V;

  EXPECT_ANY_THROW(data.reserve(data.max_size() + 1));
}

TEST(Method, swap) {
  DEFUALT_V;
  s21::vector<int> data_2{2, 3, 4, 5, 6};

  std::vector<int> data_std{1, 2, 3, 4};
  std::vector<int> data_std_2{2, 3, 4, 5, 6};

  ASSERT_EQ(data.size(), 4);
  data.swap(data_2);
  data_std.swap(data_std_2);
  ASSERT_EQ(data.size(), 5);
  ASSERT_EQ(data.size(), data_std.size());
  ASSERT_EQ(data[4], 6);
}

TEST(Method, shrink_to_fit) {
  std::vector<int> vec(1000);
  s21::vector<int> vec2(1000);
  vec.clear();
  vec2.clear();
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec2.size(), 0);
  vec.shrink_to_fit();
  vec2.shrink_to_fit();
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
  ASSERT_EQ(vec2.size(), 0);
  ASSERT_EQ(vec2.capacity(), 0);
}

TEST(Method, shrink_to_fit_2) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};

  data.reserve(50);
  data_std.reserve(50);
  ASSERT_EQ(data.size(), 4);
  data.shrink_to_fit();
  data_std.shrink_to_fit();
  ASSERT_EQ(data.capacity(), data_std.capacity());
  ASSERT_EQ(data.size(), data_std.size());
}

TEST(Method, push_back) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};
  data.push_back(5);
  data_std.push_back(5);
  ASSERT_EQ(*(data.end() - 1), *(data_std.end() - 1));
}

TEST(Method, insert) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};
  data.insert(data.begin() + 2, 100);
  data_std.insert(data_std.begin() + 2, 100);
  ASSERT_EQ(data[2], 100);
  ASSERT_EQ(data[2], data_std[2]);
}

TEST(Method, erase) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};
  data.erase(data.begin() + 2);
  data_std.erase(data_std.begin() + 2);
  ASSERT_EQ(data[2], 4);
  ASSERT_EQ(data[2], data_std[2]);
}

TEST(Method, pop_back) {
  DEFUALT_V;
  std::vector<int> data_std{1, 2, 3, 4};
  data.pop_back();
  data_std.pop_back();
  ASSERT_EQ(data.size(), 3);
  ASSERT_EQ(data[3], data_std[3]);

  for (size_t i = 0; i < data_std.size(); i++) {
    ASSERT_EQ(data[i], data_std[i]);
  }
}

TEST(Method, insert_many) {
  s21::vector<int> v;
  v.insert_many_back(1, 4, 5, 6);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 4);
  ASSERT_EQ(v[2], 5);
  ASSERT_EQ(v[3], 6);
}