#include "s21_test.h"

TEST(Multiset, DefaultConstructor) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);

  s21::multiset<std::string> ms2;
  EXPECT_TRUE(ms2.empty());
  EXPECT_EQ(ms2.size(), 0);

  s21::multiset<double> ms3;
  ms3.insert(3.14);
  EXPECT_FALSE(ms3.empty());
  EXPECT_EQ(ms3.size(), 1);
  EXPECT_TRUE(ms3.contains(3.14));

  s21::multiset<char> ms4;
  ms4.insert('a');
  ms4.insert('b');
  ms4.insert('a');
  EXPECT_EQ(ms4.size(), 3);
  EXPECT_EQ(ms4.count('a'), 2);
  EXPECT_EQ(ms4.count('b'), 1);
  ms4.clear();
  EXPECT_TRUE(ms4.empty());
}

TEST(Multiset, InitializerListConstructor) {
  s21::multiset<int> ms = {1, 2, 3, 2, 4, 1};

  EXPECT_EQ(ms.size(), 6);
  EXPECT_FALSE(ms.empty());

  EXPECT_EQ(ms.count(1), 2);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 1);
  EXPECT_EQ(ms.count(4), 1);

  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_FALSE(ms.contains(5));

  std::initializer_list<int> init_list({5, 0, 5, 10, -30, 43, 10});
  s21::multiset<int> my_set(init_list);
  std::multiset<int> std_set(init_list);

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_EQ(my_set.empty(), std_set.empty());

  s21::multiset<int>::iterator my_set_iter = my_set.begin();
  std::multiset<int>::iterator std_set_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
    ++my_set_iter;
    ++std_set_iter;
  }
}

TEST(Multiset, CopyConstructor) {
  s21::multiset<int> original = {1, 2, 3, 2, 4, 1};
  s21::multiset<int> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.size(), 6);

  for (int i = 1; i <= 4; ++i) {
    EXPECT_EQ(copy.count(i), original.count(i));
  }

  EXPECT_EQ(copy.count(1), 2);
  EXPECT_EQ(copy.count(2), 2);
  EXPECT_EQ(copy.count(3), 1);
  EXPECT_EQ(copy.count(4), 1);

  original.insert(5);
  EXPECT_TRUE(original.contains(5));
  EXPECT_FALSE(copy.contains(5));

  copy.insert(6);
  EXPECT_TRUE(copy.contains(6));
  EXPECT_FALSE(original.contains(6));

  std::initializer_list<int> init_list({1, 0, 10, -10, -30, 3, 1});
  s21::multiset<int> A(init_list);
  std::multiset<int> expected_A(init_list);
  s21::multiset<int> copy1(A);
  std::multiset<int> expected_copy1(expected_A);
  s21::multiset<int> copy2(A);

  std::multiset<int> expected_copy2;
  expected_copy2 = expected_A;

  s21::multiset<int>::iterator A_iter = A.begin();
  std::multiset<int>::iterator expected_A_iter = expected_A.begin();
  s21::multiset<int>::iterator copy1_iter = copy1.begin();
  std::multiset<int>::iterator expected_copy1_iter = expected_copy1.begin();
  s21::multiset<int>::iterator copy2_iter = copy2.begin();
  std::multiset<int>::iterator expected_copy2_iter = expected_copy2.begin();

  size_t size = expected_A.size();
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(*A_iter, *expected_A_iter);
    EXPECT_EQ(*copy1_iter, *expected_copy1_iter);
    EXPECT_EQ(*copy2_iter, *expected_copy2_iter);
    ++A_iter;
    ++expected_A_iter;
    ++copy1_iter;
    ++expected_copy1_iter;
    ++copy2_iter;
    ++expected_copy2_iter;
  }

  size = expected_A.size();
  A_iter = A.begin();
  expected_A_iter = expected_A.begin();
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(*A_iter, *expected_A_iter);
    ++A_iter;
    ++expected_A_iter;
  }
}

TEST(Multiset, MoveConstructor) {
  s21::multiset<int> original = {1, 2, 3, 2, 4, 1};
  s21::multiset<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 6);
  EXPECT_TRUE(original.empty());

  EXPECT_EQ(moved.count(1), 2);
  EXPECT_EQ(moved.count(2), 2);
  EXPECT_EQ(moved.count(3), 1);
  EXPECT_EQ(moved.count(4), 1);

  EXPECT_TRUE(moved.contains(1));
  EXPECT_TRUE(moved.contains(2));
  EXPECT_TRUE(moved.contains(3));
  EXPECT_TRUE(moved.contains(4));

  moved.insert(5);
  EXPECT_TRUE(moved.contains(5));
  EXPECT_EQ(moved.size(), 7);

  s21::multiset<int> another_move(std::move(moved));
  EXPECT_TRUE(moved.empty());
  EXPECT_EQ(another_move.size(), 7);
  EXPECT_TRUE(another_move.contains(5));
}

TEST(Multiset, MoveAssignmentOperator) {
  s21::multiset<int> ms1 = {1, 2, 3, 2, 1};
  s21::multiset<int> ms2 = {4, 5, 6};

  ms2 = std::move(ms1);

  EXPECT_EQ(ms2.size(), 5);
  EXPECT_TRUE(ms1.empty());

  EXPECT_EQ(ms2.count(1), 2);
  EXPECT_EQ(ms2.count(2), 2);
  EXPECT_EQ(ms2.count(3), 1);

  EXPECT_FALSE(ms2.contains(4));
  EXPECT_FALSE(ms2.contains(5));
  EXPECT_FALSE(ms2.contains(6));

  s21::multiset<int> ms3;
  ms3 = std::move(ms2);

  EXPECT_EQ(ms3.size(), 5);
  EXPECT_TRUE(ms2.empty());

  ms1 = std::move(ms1);
  EXPECT_TRUE(ms1.empty());
}

TEST(Multiset, BeginEnd) {
  s21::multiset<int> my_set = {1, 2, 3, 2, 1};

  auto it_begin_my_set = my_set.begin();
  auto it_end_my_set = my_set.end();

  EXPECT_EQ(*it_begin_my_set, 1);
  EXPECT_NE(it_begin_my_set, it_end_my_set);

  std::vector<int> elements;
  for (auto it = my_set.begin(); it != my_set.end(); ++it) {
    elements.push_back(*it);
  }

  EXPECT_EQ(elements.size(), 5);
  EXPECT_EQ(elements[0], 1);
  EXPECT_EQ(elements[1], 1);
  EXPECT_EQ(elements[2], 2);
  EXPECT_EQ(elements[3], 2);
  EXPECT_EQ(elements[4], 3);

  s21::multiset<int> empty_ms;
  EXPECT_EQ(empty_ms.begin(), empty_ms.end());
}

TEST(Multiset, EmptySizeMaxSize) {
  s21::multiset<int> empty_ms;
  EXPECT_TRUE(empty_ms.empty());
  EXPECT_EQ(empty_ms.size(), 0);

  s21::multiset<int> ms = {1, 2, 3, 2, 1};
  EXPECT_FALSE(ms.empty());
  EXPECT_EQ(ms.size(), 5);

  ms.insert(4);
  EXPECT_EQ(ms.size(), 6);

  ms.erase(ms.find(2));
  EXPECT_EQ(ms.size(), 5);

  while (!ms.empty()) {
    ms.erase(ms.begin());
  }
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);

  s21::multiset<int> large_ms;
  std::multiset<int> std_large_ms;

  EXPECT_EQ(large_ms.max_size(), std_large_ms.max_size());
}

TEST(Multiset, Clear) {
  s21::multiset<int> ms = {1, 2, 3, 2, 1};

  EXPECT_EQ(ms.size(), 5);
  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);

  ms.insert(4);
  EXPECT_EQ(ms.size(), 1);
  ms.clear();
  EXPECT_TRUE(ms.empty());

  s21::multiset<std::string> string_ms = {"apple", "banana", "apple", "cherry"};
  string_ms.clear();
  EXPECT_TRUE(string_ms.empty());

  s21::multiset<int> empty_ms;
  empty_ms.clear();
  EXPECT_TRUE(empty_ms.empty());
}

TEST(Multiset, Insert) {
  s21::multiset<int> ms;
  std::multiset<int> std_ms;

  auto it1 = ms.insert(5);
  auto std_it1 = std_ms.insert(5);

  EXPECT_EQ(*it1, *std_it1);
  EXPECT_EQ(ms.size(), std_ms.size());

  s21::multiset<int> ms2;
  ms2.insert(3);
  ms2.insert(3);
  ms2.insert(3);

  EXPECT_EQ(ms2.size(), 3);
  EXPECT_EQ(ms2.count(3), 3);

  s21::multiset<std::string> ms3 = {"hello", "world"};
  std::multiset<std::string> std_ms3 = {"hello", "world"};

  ms3.insert("hello");
  std_ms3.insert("hello");

  ms3.insert("ok");
  std_ms3.insert("ok");

  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(*ms.begin(), *std_ms.begin());
}

TEST(Multiset, EraseIterator) {
  s21::multiset<int> ms = {1, 2, 3, 2, 1, 4, 5};
  std::multiset<int> std_ms = {1, 2, 3, 2, 1, 4, 5};

  auto it = ms.find(3);
  ms.erase(it);
  std_ms.erase(std_ms.find(3));

  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_FALSE(ms.contains(3));

  it = ms.find(2);
  ms.erase(it);
  std_ms.erase(std_ms.find(2));

  EXPECT_EQ(ms.count(2), std_ms.count(2));
  EXPECT_EQ(ms.size(), std_ms.size());

  it = ms.find(1);
  ms.erase(it);
  std_ms.erase(std_ms.find(1));

  EXPECT_EQ(ms.count(1), std_ms.count(1));
  EXPECT_EQ(ms.size(), std_ms.size());

  while (!ms.empty()) {
    ms.erase(ms.begin());
  }
  EXPECT_TRUE(ms.empty());

  s21::multiset<int> ms2 = {1, 1, 1, 1, 1, 4, 5};
  std::multiset<int> std_ms2 = {1, 1, 1, 1, 1, 4, 5};

  auto it2 = ms2.find(1);
  ms2.erase(it2);
  std_ms2.erase(std_ms2.find(1));
  EXPECT_EQ(ms2.size(), std_ms2.size());
  for (auto it = ms2.begin(); it != ms2.end(); ++it) {
    EXPECT_EQ(*it, *std_ms2.find(*it));
  }

  s21::multiset<std::string> ms3 = {"apple", "banana", "cherry", "mango",
                                    "banana"};

  auto it3 = ms3.find("cherry");
  ms3.erase(it3);

  EXPECT_EQ(ms3.size(), 4);
  EXPECT_FALSE(ms3.contains("cherry"));

  it3 = ms3.find("banana");
  ms3.erase(it3);

  EXPECT_EQ(ms3.size(), 3);
  EXPECT_EQ(ms3.count("banana"), 1);
}

TEST(Multiset, Swap) {
  s21::multiset<int> ms1 = {1, 2, 3, 2, 1};
  s21::multiset<int> ms2 = {4, 5, 6, 5, 4};

  ms1.swap(ms2);

  EXPECT_EQ(ms1.size(), 5);
  EXPECT_EQ(ms2.size(), 5);
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms1.contains(5));
  EXPECT_TRUE(ms1.contains(6));
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));

  s21::multiset<std::string> ms11 = {"apple", "banana", "cherry"};
  s21::multiset<std::string> ms21;

  ms11.swap(ms21);

  EXPECT_TRUE(ms11.empty());
  EXPECT_EQ(ms21.size(), 3);
  EXPECT_TRUE(ms21.contains("apple"));
  EXPECT_TRUE(ms21.contains("banana"));
  EXPECT_TRUE(ms21.contains("cherry"));

  s21::multiset<int> ms = {1, 2, 3};
  s21::multiset<int>& ref = ms;

  ms.swap(ref);

  EXPECT_EQ(ms.size(), 3);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
}

TEST(Multiset, Merge) {
  s21::multiset<int> ms1 = {1, 3, 5};
  s21::multiset<int> ms2 = {2, 4, 6};
  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 6);
  EXPECT_TRUE(ms2.empty());
  for (int i = 1; i <= 6; ++i) {
    EXPECT_TRUE(ms1.contains(i));
  }

  s21::multiset<int> ms11 = {1, 2, 3, 2};
  s21::multiset<int> ms21 = {2, 3, 4, 3};
  ms11.merge(ms21);

  EXPECT_EQ(ms11.size(), 8);
  EXPECT_TRUE(ms21.empty());
  EXPECT_EQ(ms11.count(2), 3);
  EXPECT_EQ(ms11.count(3), 3);

  s21::multiset<std::string> ms12;
  s21::multiset<std::string> ms22;
  ms12.merge(ms22);

  EXPECT_TRUE(ms12.empty());
  EXPECT_TRUE(ms22.empty());

  s21::multiset<double> ms13;
  s21::multiset<double> ms23 = {1.1, 2.2, 3.3};
  ms13.merge(ms23);

  EXPECT_EQ(ms13.size(), 3);
  EXPECT_TRUE(ms23.empty());
  EXPECT_TRUE(ms13.contains(1.1));
  EXPECT_TRUE(ms13.contains(2.2));
  EXPECT_TRUE(ms13.contains(3.3));
}

TEST(Multiset, Count) {
  s21::multiset<int> ms = {1, 2, 3, 2, 1, 4, 5};

  EXPECT_EQ(ms.count(1), 2);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 1);
  EXPECT_EQ(ms.count(4), 1);
  EXPECT_EQ(ms.count(5), 1);
  EXPECT_EQ(ms.count(6), 0);

  s21::multiset<std::string> ms2 = {"apple",  "banana", "cherry",
                                    "banana", "mango",  "banana"};

  EXPECT_EQ(ms2.count("apple"), 1);
  EXPECT_EQ(ms2.count("banana"), 3);
  EXPECT_EQ(ms2.count("cherry"), 1);
  EXPECT_EQ(ms2.count("mango"), 1);
  EXPECT_EQ(ms2.count("grape"), 0);
  ms2.clear();
  EXPECT_TRUE(ms2.empty());
  EXPECT_EQ(ms2.count("banana"), 0);

  s21::multiset<double> ms3;
  EXPECT_EQ(ms3.count(3.14), 0);
}

TEST(Multiset, Find) {
  s21::multiset<int> ms = {1, 2, 3, 2, 1, 4, 5};

  auto it = ms.find(3);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 3);

  it = ms.find(6);
  EXPECT_EQ(it, ms.end());

  s21::multiset<std::string> ms2 = {"apple", "banana", "cherry", "banana",
                                    "mango"};

  auto it2 = ms2.find("banana");
  EXPECT_NE(it2, ms2.end());
  EXPECT_EQ(*it2, "banana");

  it2 = ms2.find("grape");
  EXPECT_EQ(it2, ms2.end());

  s21::multiset<int> ms3;
  auto it3 = ms3.find(1);
  EXPECT_EQ(it3, ms3.end());
}

TEST(Multiset, Contains) {
  s21::multiset<int> ms = {1, 2, 3, 2, 1, 4, 5};

  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_TRUE(ms.contains(4));
  EXPECT_TRUE(ms.contains(5));
  EXPECT_FALSE(ms.contains(6));
  ms.insert(6);
  EXPECT_TRUE(ms.contains(6));
  ms.clear();
  EXPECT_FALSE(ms.contains(6));

  s21::multiset<int> ms2;

  EXPECT_FALSE(ms2.contains(1));
}

TEST(Multiset, EqualRange) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 5};

  auto range = ms.equal_range(3);
  EXPECT_EQ(*(--range.first), 2);
  EXPECT_EQ(*range.second, 4);

  range = ms.equal_range(6);
  EXPECT_EQ(range.first, range.second);
  EXPECT_EQ(range.first, ms.end());

  s21::multiset<std::string> ms2 = {"apple", "banana", "banana", "cherry",
                                    "date"};

  auto range2 = ms2.equal_range("banana");
  EXPECT_EQ(*range2.first, "banana");
  range2.first++;
  range2.first++;
  EXPECT_EQ(*range2.first, *range2.second);
  EXPECT_EQ(*(--range2.second), "banana");

  range2 = ms2.equal_range("grape");
  EXPECT_EQ(range2.first, range2.second);
  EXPECT_EQ(range2.first, ms2.end());

  s21::multiset<int> ms3;

  auto range3 = ms3.equal_range(1);
  EXPECT_EQ(range3.first, range3.second);
  EXPECT_EQ(range3.first, ms3.end());
}

TEST(Multiset, LowerBound) {
  s21::multiset<int> ms = {1, 2, 2, 3, 4, 5};

  auto it = ms.lower_bound(2);
  EXPECT_EQ(*it, 2);

  it = ms.lower_bound(0);
  EXPECT_EQ(*it, 1);

  it = ms.lower_bound(6);
  EXPECT_EQ(it, ms.end());

  s21::multiset<std::string> ms2 = {"apple", "banana", "cherry", "mango"};

  auto it2 = ms2.lower_bound("banana");
  EXPECT_EQ(*it2, "banana");

  it2 = ms2.lower_bound("carrot");
  EXPECT_EQ(*it2, "cherry");

  s21::multiset<int> ms3;

  auto it3 = ms3.lower_bound(1);
  EXPECT_EQ(it3, ms3.end());
}

TEST(Multiset, UpperBound) {
  s21::multiset<int> ms = {1, 2, 2, 3, 4, 5};

  auto it = ms.upper_bound(2);
  EXPECT_EQ(*it, 3);

  it = ms.upper_bound(0);
  EXPECT_EQ(*it, 1);

  it = ms.upper_bound(5);
  EXPECT_EQ(it, ms.end());

  s21::multiset<std::string> ms2 = {"apple", "banana", "cherry"};

  auto it2 = ms2.upper_bound("banana");
  EXPECT_EQ(*it2, "cherry");

  it2 = ms2.upper_bound("carrot");
  EXPECT_EQ(*it2, "cherry");

  s21::multiset<int> ms3;

  auto it3 = ms3.upper_bound(1);
  EXPECT_EQ(it3, ms3.end());
}

TEST(Multiset, InsertMany) {
  s21::multiset<int> ms;
  auto result = ms.insert_many(1, 2, 3, 2, 1);

  EXPECT_EQ(result.size(), 5);
  for (const auto& pair : result) {
    EXPECT_TRUE(pair.second);
  }
  EXPECT_EQ(ms.size(), 5);
  EXPECT_EQ(ms.count(1), 2);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 1);

  s21::multiset<std::string> ms2 = {"apple", "banana"};
  auto result2 = ms2.insert_many("apple", "banana", "cherry", "banana");

  EXPECT_EQ(result2.size(), 4);
  for (const auto& pair : result2) {
    EXPECT_TRUE(pair.second);
  }
  EXPECT_EQ(ms2.size(), 6);
  EXPECT_EQ(ms2.count("apple"), 2);
  EXPECT_EQ(ms2.count("banana"), 3);
  EXPECT_EQ(ms2.count("cherry"), 1);

  s21::multiset<int> ms3;
  auto result3 = ms3.insert_many();

  EXPECT_TRUE(result3.empty());
  EXPECT_TRUE(ms3.empty());
}