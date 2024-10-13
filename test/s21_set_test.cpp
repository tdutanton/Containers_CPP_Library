#include "s21_test.h"

TEST(Set, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.begin(), s.end());
  EXPECT_FALSE(s.contains(1));
}

TEST(Set, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3, 4, 5};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
  auto iter = s.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
  ++iter;
  EXPECT_EQ(iter, s.end());

  s21::set<int> s2 = {1, 2, 2, 3, 3, 3, 4, 5, 5};
  EXPECT_EQ(s2.size(), 5);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_TRUE(s2.contains(4));
  EXPECT_TRUE(s2.contains(5));

  s21::set<int> s3 = {};
  EXPECT_TRUE(s3.empty());
  EXPECT_EQ(s3.begin(), s3.end());
  EXPECT_EQ(s3.size(), 0);
}

TEST(Set, CopyConstructor) {
  s21::set<int> original = {1, 2, 3, 4, 5};
  s21::set<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(copy.size(), 5);

  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(copy.contains(i));
  }

  s21::set<int> original2;
  s21::set<int> copy2(original2);

  EXPECT_TRUE(copy2.empty());
  EXPECT_EQ(copy2.size(), 0);

  s21::set<std::string> s5 = {"apple", "banana", "cherry", "lime"};
  s21::set<std::string> s4(s5);
  s5.erase(s5.find("banana"));
  EXPECT_EQ(s4.size(), 4);
  EXPECT_TRUE(s4.contains("apple"));
  EXPECT_TRUE(s4.contains("banana"));
  EXPECT_TRUE(s4.contains("cherry"));
  EXPECT_TRUE(s4.contains("lime"));
  EXPECT_FALSE(s4.contains("grape"));
}

TEST(Set, MoveConstructor) {
  s21::set<int> original = {1, 2, 3, 4, 5};
  s21::set<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 5);
  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(moved.contains(i));
  }

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(original.size(), 0);

  s21::set<int> original1;
  s21::set<int> moved1;
  moved1 = std::move(original1);

  EXPECT_TRUE(moved1.empty());
  EXPECT_EQ(moved1.size(), 0);
  EXPECT_TRUE(original1.empty());
}

TEST(Set, MoveAssignmentOperator) {
  s21::set<int> original = {1, 2, 3, 4, 5};
  s21::set<int> assigned;
  assigned = std::move(original);

  EXPECT_EQ(assigned.size(), 5);
  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(assigned.contains(i));
  }

  EXPECT_TRUE(original.empty());

  s21::set<int> original1;
  s21::set<int> assigned1 = {10, 20, 30};
  assigned1 = std::move(original1);

  EXPECT_TRUE(assigned1.empty());
  EXPECT_TRUE(original1.empty());

  s21::set<std::string> original2 = {"apple", "banana", "cherry"};
  s21::set<std::string> assigned2 = {"dog", "cat", "bird"};
  assigned2 = std::move(original2);

  EXPECT_EQ(assigned2.size(), 3);
  EXPECT_TRUE(assigned2.contains("apple"));
  EXPECT_TRUE(assigned2.contains("banana"));
  EXPECT_TRUE(assigned2.contains("cherry"));
  EXPECT_FALSE(assigned2.contains("dog"));
  EXPECT_FALSE(assigned2.contains("cat"));
  EXPECT_FALSE(assigned2.contains("bird"));

  EXPECT_TRUE(original2.empty());
}

TEST(Set, BeginEndIterators) {
  s21::set<int> s;
  EXPECT_EQ(s.begin(), s.end());
  auto s_end = s.end();
  ++s_end;
  EXPECT_EQ(s_end, s.end());

  s21::set<int> s1 = {1, 2, 3, 4, 5};
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);

  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
  EXPECT_EQ(it, s1.end());

  s21::set<std::string> fruits = {"apple", "banana", "cherry"};
  auto iter = fruits.begin();
  iter--;
  EXPECT_EQ(iter, fruits.begin());
  iter = fruits.end();
  --iter;
  EXPECT_EQ(*iter, "cherry");
  iter++;
  iter++;
  EXPECT_EQ(iter, fruits.end());

  iter = fruits.begin();
  EXPECT_EQ(*iter, "apple");
  ++iter;
  EXPECT_EQ(*iter, "banana");
  ++iter;
  EXPECT_EQ(*iter, "cherry");
  ++iter;
  EXPECT_EQ(iter, fruits.end());
}

TEST(Set, EmptySizeMax_size) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  s21::set<std::string> s2 = {"apple", "banana", "cherry"};
  EXPECT_EQ(s2.size(), 3);
  EXPECT_FALSE(s2.empty());

  s2.erase(s2.find("apple"));
  s2.erase(s2.find("banana"));
  s2.erase(s2.find("cherry"));
  EXPECT_TRUE(s2.empty());
  EXPECT_EQ(s2.size(), 0);

  s2.insert("watermelon");
  EXPECT_EQ(s2.size(), 1);
  EXPECT_FALSE(s2.empty());

  s21::set<int> s3;
  std::set<int> s4;
  EXPECT_EQ(s3.max_size(), s4.max_size());
}

TEST(Set, Clear) {
  s21::set<int> s;
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  s = {1, 2, 3, 4, 5};
  EXPECT_TRUE(s.contains(1));
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  s21::set<std::string> s1 = {"apple", "banana", "cherry"};
  s1.clear();
  EXPECT_TRUE(s1.empty());
  s1.insert("watermelon");
  EXPECT_FALSE(s1.empty());
  EXPECT_EQ(s1.size(), 1);

  s21::set<float> s2 = {1.8, 2.9, 3.4};
  s2.clear();
  s2.clear();
  EXPECT_TRUE(s2.empty());
  EXPECT_EQ(s2.size(), 0);
}

TEST(Set, Insert) {
  s21::set<int> s;
  s = {1, 2, 3};
  auto result = s.insert(5);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(*(result.first), 5);
  EXPECT_EQ(s.size(), 4);

  auto result2 = s.insert(2);
  EXPECT_FALSE(result2.second);
  EXPECT_EQ(*(result2.first), 2);
  EXPECT_EQ(s.size(), 4);

  s21::set<std::string> my_set;
  my_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("test");
  EXPECT_TRUE(my_pr.second);
  auto my_pr2 = my_set.insert("is");
  EXPECT_FALSE(my_pr2.second);

  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set{};
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_TRUE(my_empty_set.empty());
  EXPECT_TRUE(my_empty_set.size() == 0);
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  EXPECT_TRUE(my_empty_set.empty());
  EXPECT_TRUE(my_empty_set.size() == 0);
}

TEST(Set, Erase) {
  s21::set<int> s = {1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));

  s21::set<int> s2 = {1, 2, 3, 4, 5};
  auto it2 = s2.begin();
  s2.erase(it2);
  EXPECT_EQ(s2.size(), 4);
  EXPECT_FALSE(s2.contains(1));
  EXPECT_EQ(*s2.begin(), 2);

  s21::set<std::string> s3 = {"apple", "banana", "cherry"};
  auto it3 = s3.find("banana");
  s3.erase(it3);
  EXPECT_EQ(s3.size(), 2);
  EXPECT_FALSE(s3.contains("banana"));
  s3.insert("banana");
  EXPECT_EQ(s3.size(), 3);
  EXPECT_TRUE(s3.contains("banana"));
  s3.clear();
  EXPECT_TRUE(s3.empty());
  s3.insert("mango");
  EXPECT_EQ(s3.size(), 1);
  EXPECT_TRUE(s3.contains("mango"));

  s21::set<int> s4 = {1, 2, 3};
  while (!s4.empty()) {
    s4.erase(s4.begin());
  }
  EXPECT_TRUE(s4.empty());

  s21::set<int> s5 = {1, 2, 3, 4, 5};
  auto it5 = s5.find(5);
  s5.erase(it5);
  EXPECT_EQ(s5.size(), 4);
  EXPECT_FALSE(s5.contains(5));
}

TEST(Set, Swap) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_TRUE(s1.contains(4) && s1.contains(5) && s1.contains(6));
  EXPECT_TRUE(s2.contains(1) && s2.contains(2) && s2.contains(3));
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);

  s21::set<int> s11;
  s21::set<int> s21 = {1, 2, 3};
  s11.swap(s21);
  EXPECT_TRUE(s11.contains(1) && s11.contains(2) && s11.contains(3));
  EXPECT_TRUE(s21.empty());
  EXPECT_EQ(s11.size(), 3);
  EXPECT_EQ(s21.size(), 0);

  s21::set<int> s12;
  s21::set<int> s22;
  s12.swap(s22);
  EXPECT_TRUE(s12.empty());
  EXPECT_TRUE(s22.empty());

  s21::set<std::string> s13 = {"apple", "banana"};
  s21::set<std::string> s23 = {"cherry", "mango"};
  s13.swap(s23);
  s13.insert("elderberry");
  EXPECT_TRUE(s13.contains("cherry") && s13.contains("mango") &&
              s13.contains("elderberry"));
  EXPECT_TRUE(s23.contains("apple") && s23.contains("banana"));
  EXPECT_EQ(s13.size(), 3);
  EXPECT_EQ(s23.size(), 2);

  s23.clear();
  EXPECT_TRUE(s23.empty());
  s23.swap(s13);
  EXPECT_TRUE(s23.contains("cherry") && s23.contains("mango"));
  EXPECT_EQ(s23.size(), 3);
  EXPECT_EQ(s13.size(), 0);
}

TEST(Set, Merge) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 6);
  EXPECT_TRUE(s1.contains(1) && s1.contains(2) && s1.contains(3) &&
              s1.contains(4) && s1.contains(5) && s1.contains(6));
  EXPECT_TRUE(s2.empty());

  s21::set<int> s12 = {1, 2, 3, 4};
  s21::set<int> s22 = {3, 4, 5, 6};
  s12.merge(s22);
  EXPECT_EQ(s12.size(), 6);
  for (int i = 1; i <= 6; ++i) {
    EXPECT_TRUE(s12.contains(i));
  }
  EXPECT_EQ(s22.size(), 2);
  EXPECT_TRUE(s22.contains(3) && s22.contains(4));

  s21::set<int> s13 = {1, 2, 3};
  s21::set<int> s23;
  s13.merge(s23);
  EXPECT_EQ(s13.size(), 3);
  EXPECT_TRUE(s13.contains(1) && s13.contains(2) && s13.contains(3));
  EXPECT_TRUE(s23.empty());

  s21::set<int> s14;
  s21::set<int> s24 = {1, 2, 3};
  s14.merge(s24);
  EXPECT_EQ(s14.size(), 3);
  EXPECT_TRUE(s14.contains(1) && s14.contains(2) && s14.contains(3));
  EXPECT_TRUE(s24.empty());
}

TEST(Set, IteratorFind) {
  s21::set<int> s = {1, 3, 5, 7, 9};
  auto it = s.find(5);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 5);

  s21::set<int> s1 = {1, 3, 5, 7, 9};
  auto it1 = s1.find(4);
  EXPECT_EQ(it1, s1.end());

  s21::set<int> s2;
  auto it2 = s2.find(1);
  EXPECT_EQ(it2, s2.end());

  s21::set<std::string> s3 = {"apple", "banana", "cherry", "mango"};
  auto it_first = s3.find("apple");
  auto it_last = s3.find("mango");
  EXPECT_NE(it_first, s3.end());
  EXPECT_NE(it_last, s3.end());
  EXPECT_EQ(*it_first, "apple");
  EXPECT_EQ(*it_last, "mango");
}

TEST(Set, Contains) {
  s21::set<int> s = {1, 3, 5, 7, 9};
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(9));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(4));
  s.insert(4);
  EXPECT_TRUE(s.contains(4));
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(s.contains(4));

  s21::set<int> s1;
  EXPECT_FALSE(s1.contains(1));

  s21::set<std::string> s2;
  s2.insert("apple");
  EXPECT_TRUE(s2.contains("apple"));
  EXPECT_FALSE(s2.contains("banana"));

  s21::set<char> s3 = {'a', 'b', 'c'};
  s3.erase(s3.find('b'));
  EXPECT_TRUE(s3.contains('a'));
  EXPECT_FALSE(s3.contains('b'));
  EXPECT_TRUE(s3.contains('c'));
}

TEST(Set, InsertMany) {
  s21::set<int> s;
  auto result = s.insert_many(1, 2, 3, 4, 5);

  EXPECT_EQ(result.size(), 5);
  for (const auto& pair : result) {
    EXPECT_TRUE(pair.second);
  }
  EXPECT_EQ(s.size(), 5);
  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(s.contains(i));
  }

  s21::set<int> s2{1, 2, 3};
  auto result2 = s2.insert_many(2, 3, 4, 5);

  ASSERT_EQ(result2.size(), 4);
  EXPECT_FALSE(result2[0].second);
  EXPECT_FALSE(result2[1].second);
  EXPECT_TRUE(result2[2].second);
  EXPECT_TRUE(result2[3].second);
  EXPECT_EQ(s2.size(), 5);
  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(s2.contains(i));
  }

  s21::set<int> s3;
  auto result3 = s3.insert_many();

  EXPECT_TRUE(result3.empty());
  EXPECT_TRUE(s3.empty());

  s21::set<std::string> s4;
  auto result4 = s4.insert_many("one", "two", "three");

  ASSERT_EQ(result4.size(), 3);
  for (const auto& pair : result4) {
    EXPECT_TRUE(pair.second);
  }
  EXPECT_EQ(s4.size(), 3);
  EXPECT_TRUE(s4.contains("one"));
  EXPECT_TRUE(s4.contains("two"));
  EXPECT_TRUE(s4.contains("three"));
}