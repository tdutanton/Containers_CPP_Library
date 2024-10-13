#include "s21_test.h"

TEST(Map, DefaultConstructor) {
  s21::map<int, std::string> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
  auto it = m.begin();
  EXPECT_EQ(it, m.end());
  EXPECT_FALSE(m.contains(1));
}

TEST(Map, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m[2], "two");
  EXPECT_EQ(m[3], "three");

  EXPECT_FALSE(m.empty());
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));

  auto it = m.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");
  ++it;
  EXPECT_EQ(it, m.end());

  s21::map<int, std::string> m2{{1, "one"}, {2, "two"}, {1, "uno"}};

  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[1], "one");
}

TEST(Map, CopyConstructor) {
  s21::map<int, std::string> m1{{1, "one"}, {2, "two"}};
  s21::map<int, std::string> m2(m1);
  EXPECT_EQ(m2.size(), m1.size());
  EXPECT_EQ(m2[1], m1[1]);
  EXPECT_EQ(m2[2], m1[2]);

  s21::map<int, std::string> original{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy[1], "one");
  EXPECT_EQ(copy[2], "two");
  EXPECT_EQ(copy[3], "three");

  original[4] = "four";
  EXPECT_NE(copy.size(), original.size());
  EXPECT_FALSE(copy.contains(4));

  copy[5] = "five";
  EXPECT_EQ(copy.size(), 4);
  EXPECT_EQ(original.size(), 4);
  EXPECT_FALSE(original.contains(5));

  s21::map<int, std::string> original2;
  s21::map<int, std::string> copy2(original2);

  EXPECT_TRUE(copy2.empty());
  EXPECT_EQ(copy2.size(), 0);
}

TEST(Map, MoveConstructor) {
  s21::map<int, std::string> m1{{1, "one"}, {2, "two"}};
  s21::map<int, std::string> m2(std::move(m1));
  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[1], "one");
  EXPECT_EQ(m2[2], "two");
  EXPECT_TRUE(m1.empty());

  s21::map<int, std::string> original{{1, "one"}, {2, "two"}, {3, "three"}};
  size_t originalSize = original.size();

  s21::map<int, std::string> moved(std::move(original));

  EXPECT_EQ(moved.size(), originalSize);
  EXPECT_TRUE(original.empty());

  EXPECT_EQ(moved[1], "one");
  EXPECT_EQ(moved[2], "two");
  EXPECT_EQ(moved[3], "three");

  EXPECT_FALSE(original.contains(1));
  EXPECT_FALSE(original.contains(2));
  EXPECT_FALSE(original.contains(3));

  s21::map<int, std::string> original2;
  s21::map<int, std::string> moved2(std::move(original2));

  EXPECT_TRUE(moved2.empty());
  EXPECT_TRUE(original2.empty());
}

TEST(Map, MoveAssignmentOperator) {
  s21::map<int, std::string> m1{{1, "one"}, {2, "two"}};
  s21::map<int, std::string> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[1], "one");
  EXPECT_EQ(m2[2], "two");
  EXPECT_TRUE(m1.empty());

  s21::map<int, std::string> original{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> moved;

  moved = std::move(original);

  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(original.empty());

  EXPECT_EQ(moved[1], "one");
  EXPECT_EQ(moved[2], "two");
  EXPECT_EQ(moved[3], "three");

  EXPECT_FALSE(original.contains(1));
  EXPECT_FALSE(original.contains(2));
  EXPECT_FALSE(original.contains(3));

  s21::map<int, std::string> original2;
  s21::map<int, std::string> moved2{{1, "one"}};

  moved2 = std::move(original2);

  EXPECT_TRUE(moved2.empty());
  EXPECT_TRUE(original2.empty());
}

TEST(Map, AtKey) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}};
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");

  m.at(2) = "dos";
  EXPECT_EQ(m.at(2), "dos");

  s21::map<int, std::string> m2{{1, "one"}};
  EXPECT_THROW(m2.at(2), std::out_of_range);

  s21::map<std::string, double> numbers{
      {"pi", 3.14159}, {"e", 2.71828}, {"phi", 1.61803}};

  EXPECT_DOUBLE_EQ(numbers.at("pi"), 3.14159);
  EXPECT_DOUBLE_EQ(numbers.at("e"), 2.71828);
  EXPECT_DOUBLE_EQ(numbers.at("phi"), 1.61803);

  numbers.at("e") = 2.71;
  EXPECT_DOUBLE_EQ(numbers.at("e"), 2.71);

  EXPECT_THROW(numbers.at("sqrt2"), std::out_of_range);
}

TEST(Map, OperatorBracket) {
  s21::map<int, std::string> m;
  m[1] = "one";
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m.size(), 1);

  s21::map<int, std::string> m2{{1, "one"}};
  m2[1] = "ONE";
  EXPECT_EQ(m2[1], "ONE");

  s21::map<std::string, int> fruits;

  fruits["apple"] = 5;
  EXPECT_EQ(fruits["apple"], 5);

  fruits["banana"] = 3;
  EXPECT_EQ(fruits["banana"], 3);

  fruits["apple"] = 7;
  EXPECT_EQ(fruits["apple"], 7);

  EXPECT_EQ(fruits["cherry"], 0);
  EXPECT_EQ(fruits.size(), 3);
}

TEST(Map, BeginEndIterators) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.begin(), m.end());

  s21::map<int, std::string> m2{{1, "one"}, {2, "two"}};
  auto it2 = m2.begin();
  EXPECT_NE(it2, m2.end());
  EXPECT_EQ(it2->first, 1);
  EXPECT_EQ(it2->second, "one");

  s21::map<int, std::string> m3{{1, "one"}, {2, "two"}, {3, "three"}};
  std::vector<int> keys;
  for (auto it3 = m3.begin(); it3 != m3.end(); ++it3) {
    keys.push_back(it3->first);
  }
  EXPECT_EQ(keys, std::vector<int>({1, 2, 3}));

  s21::map<int, std::string> m4{{1, "one"}};
  auto it4 = m4.begin();
  it4->second = "ONE";
  EXPECT_EQ(m4[1], "ONE");

  s21::map<int, std::string> numbers{{1, "one"}, {3, "three"}, {5, "five"}};

  auto it = numbers.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");

  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");

  ++it;
  EXPECT_EQ(it->first, 5);
  EXPECT_EQ(it->second, "five");

  ++it;
  EXPECT_EQ(it, numbers.end());

  s21::map<char, float> numbers2{{'a', 1.1f}, {'b', 2.2f}, {'c', 3.3f}};

  auto iter_numbers = numbers2.end();
  --iter_numbers;
  EXPECT_EQ(iter_numbers->first, 'c');
  EXPECT_FLOAT_EQ(iter_numbers->second, 3.3f);

  --iter_numbers;
  EXPECT_EQ(iter_numbers->first, 'b');
  EXPECT_FLOAT_EQ(iter_numbers->second, 2.2f);

  --iter_numbers;
  EXPECT_EQ(iter_numbers->first, 'a');
  EXPECT_FLOAT_EQ(iter_numbers->second, 1.1f);

  EXPECT_EQ(iter_numbers, numbers2.begin());
}

TEST(Map, EmptySizeMax_size) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.empty(), 1);
  m.clear();
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.empty(), 1);
  m.insert({1, "one"});
  m.insert({2, "two"});
  EXPECT_EQ(m.size(), 2);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 1);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 0);

  s21::map<int, int> m1 = {{1, 2345}};
  std::map<int, int> m2 = {{1, 2345}};
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(Map, Clear) {
  s21::map<int, std::string> m;
  std::map<int, std::string> std_m;

  m.clear();
  std_m.clear();
  EXPECT_EQ(m.size(), std_m.size());
  EXPECT_TRUE(m.empty());

  m[1] = "one";
  m[2] = "two";
  m[3] = "three";
  std_m[1] = "one";
  std_m[2] = "two";
  std_m[3] = "three";

  m.clear();
  std_m.clear();

  EXPECT_EQ(m.size(), std_m.size());
  EXPECT_TRUE(m.empty());

  m[4] = "four";
  std_m[4] = "four";
  EXPECT_EQ(m.size(), std_m.size());
  EXPECT_EQ(m[4], std_m[4]);
}

TEST(Map, Insert) {
  s21::map<int, std::string> m;
  std::map<int, std::string> std_m;

  auto result = m.insert({1, "one"});
  auto std_result = std_m.insert({1, "one"});
  EXPECT_EQ(result.second, std_result.second);
  EXPECT_EQ(result.first->first, std_result.first->first);
  EXPECT_EQ(result.first->second, std_result.first->second);

  result = m.insert({1, "ONE"});
  std_result = std_m.insert({1, "ONE"});
  EXPECT_EQ(result.second, std_result.second);
  EXPECT_EQ(result.first->second, std_result.first->second);

  EXPECT_EQ(m.size(), std_m.size());

  s21::map<int, std::string> m2;
  std::map<int, std::string> std_m2;

  EXPECT_TRUE(m2.insert({5, "cat"}).second);
  EXPECT_TRUE(m2.insert({3, "dog"}).second);
  EXPECT_TRUE(m2.insert({7, "elephant"}).second);

  EXPECT_FALSE(m2.insert({5, "tiger"}).second);

  auto it_m2 = m2.begin();
  while (it_m2->first != 3) {
    it_m2++;
  }
  m2.erase(it_m2);

  EXPECT_TRUE(m2.insert({1, "giraffe"}).second);
  EXPECT_TRUE(m2.insert({9, "zebra"}).second);
  EXPECT_TRUE(m2.insert(4, "penguin").second);

  std_m2.insert({{5, "cat"},
                 {7, "elephant"},
                 {1, "giraffe"},
                 {9, "zebra"},
                 {4, "penguin"}});
  EXPECT_EQ(m2.size(), std_m2.size());

  for (const auto& pair : m2) {
    EXPECT_EQ(pair.second, std_m2[pair.first]);
  }

  s21::map<std::string, int> m3;
  std::map<std::string, int> std_m3;

  m3.insert({"apple", 1});
  m3.insert({"banana", 2});
  m3.insert({"cherry", 3});

  auto it_m3 = m3.begin();
  while (it_m3->first != "banana") {
    it_m3++;
  }

  m3.erase(it_m3);

  EXPECT_TRUE(m3.insert({"date", 4}).second);
  EXPECT_TRUE(m3.insert({"elderberry", 5}).second);

  EXPECT_FALSE(m3.insert({"apple", 10}).second);

  std_m3.insert({{"apple", 1}, {"cherry", 3}, {"date", 4}, {"elderberry", 5}});
  EXPECT_EQ(m3.size(), std_m3.size());

  for (const auto& pair : m3) {
    EXPECT_EQ(pair.second, std_m3[pair.first]);
  }
}

TEST(Map, InsertOrAssign) {
  s21::map<int, std::string> m;
  std::map<int, std::string> std_m;

  auto [it1, inserted1] = m.insert_or_assign(5, "leopard");
  auto [std_it1, std_inserted1] = std_m.insert_or_assign(5, "leopard");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(std_inserted1, inserted1);
  EXPECT_EQ(it1->second, std_it1->second);

  auto [it2, inserted2] = m.insert_or_assign(5, "panther");
  auto [std_it2, std_inserted2] = std_m.insert_or_assign(5, "panther");
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(std_inserted2, inserted2);
  EXPECT_EQ(it2->second, std_it2->second);

  auto [it3, inserted3] = m.insert_or_assign(10, "jaguar");
  auto [std_it3, std_inserted3] = std_m.insert_or_assign(10, "jaguar");
  EXPECT_TRUE(inserted3);
  EXPECT_EQ(std_inserted3, inserted3);
  EXPECT_EQ(it3->second, std_it3->second);

  EXPECT_EQ(m.size(), std_m.size());
  for (const auto& [key, value] : m) {
    EXPECT_EQ(value, std_m[key]);
  }
}

TEST(Map, EraseIterator) {
  s21::map<int, std::string> m;

  m.insert({1, "cat"});
  m.insert({3, "dog"});
  m.insert({5, "elephant"});
  m.insert({7, "giraffe"});
  m.insert({9, "hippo"});

  auto it = m.insert_or_assign(5, "elephant").first;
  m.erase(it);
  EXPECT_EQ(m.size(), 4);

  it = m.begin();
  m.erase(it);
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.begin()->first, 3);

  it = --m.end();
  m.erase(it);
  EXPECT_EQ(m.size(), 2);
  EXPECT_EQ((--m.end())->first, 7);

  EXPECT_EQ(m[3], "dog");
  EXPECT_EQ(m[7], "giraffe");
}

TEST(Map, Swap) {
  s21::map<int, std::string> m1{{1, "cat"}, {3, "dog"}, {5, "elephant"}};
  s21::map<int, std::string> m2{
      {2, "bear"}, {4, "fox"}, {6, "giraffe"}, {8, "hippo"}};

  size_t size1 = m1.size();
  size_t size2 = m2.size();
  std::string val1 = m1[3];
  std::string val2 = m2[4];

  m1.swap(m2);

  EXPECT_EQ(m1.size(), size2);
  EXPECT_EQ(m2.size(), size1);

  EXPECT_EQ(m2[3], val1);
  EXPECT_EQ(m1[4], val2);

  EXPECT_TRUE(m1.contains(2));
  EXPECT_TRUE(m1.contains(8));
  EXPECT_FALSE(m1.contains(1));

  EXPECT_TRUE(m2.contains(1));
  EXPECT_TRUE(m2.contains(5));
  EXPECT_FALSE(m2.contains(2));

  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> m3{{10, "jaguar"}, {20, "kangaroo"}};

  m3.swap(empty_map);

  EXPECT_TRUE(m3.empty());
  EXPECT_EQ(empty_map.size(), 2);
  EXPECT_EQ(empty_map[10], "jaguar");
}

TEST(Map, Merge) {
  s21::map<int, std::string> m1{{1, "apple"}, {3, "cherry"}, {5, "elderberry"}};
  s21::map<int, std::string> m2{
      {2, "banana"}, {4, "date"}, {6, "fig"}, {3, "coconut"}};

  size_t size1 = m1.size();
  size_t size2 = m2.size();

  m1.merge(m2);

  EXPECT_EQ(m1.size(), size1 + size2 - 1);
  EXPECT_TRUE(m1.contains(2));
  EXPECT_TRUE(m1.contains(4));
  EXPECT_TRUE(m1.contains(6));

  EXPECT_EQ(m1[3], "cherry");

  EXPECT_TRUE(m2.contains(3));

  s21::map<int, std::string> empty_map;
  size_t size_before = m1.size();
  m1.merge(empty_map);
  EXPECT_EQ(m1.size(), size_before);

  s21::map<int, std::string> m3{{7, "grape"}, {8, "honeydew"}};
  empty_map.merge(m3);
  EXPECT_EQ(empty_map.size(), 2);
  EXPECT_TRUE(m3.empty());
}

TEST(Map, Contains) {
  s21::map<int, std::string> m{
      {1, "cat"}, {3, "dog"}, {5, "elephant"}, {7, "giraffe"}};

  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(3));
  EXPECT_TRUE(m.contains(5));
  EXPECT_TRUE(m.contains(7));

  EXPECT_FALSE(m.contains(0));
  EXPECT_FALSE(m.contains(2));
  EXPECT_FALSE(m.contains(4));
  EXPECT_FALSE(m.contains(6));
  EXPECT_FALSE(m.contains(8));

  m.erase(m.insert_or_assign(3, "dog").first);
  EXPECT_FALSE(m.contains(3));

  m.insert({9, "hippo"});
  EXPECT_TRUE(m.contains(9));

  s21::map<int, std::string> empty_map;
  EXPECT_FALSE(empty_map.contains(1));

  m.clear();
  EXPECT_FALSE(m.contains(1));
  EXPECT_FALSE(m.contains(5));
  EXPECT_FALSE(m.contains(9));
}

TEST(Map, InsertMany) {
  s21::map<int, std::string> m;
  auto result =
      m.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                    std::make_pair(3, "three"));

  EXPECT_EQ(result.size(), 3);
  EXPECT_TRUE(result[0].second && result[1].second && result[2].second);
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m[2], "two");
  EXPECT_EQ(m[3], "three");

  s21::map<int, std::string> m2{{1, "one"}};
  auto result2 = m2.insert_many(std::pair(1, "uno"), std::pair(2, "two"));

  EXPECT_EQ(result2.size(), 2);
  EXPECT_FALSE(result2[0].second);
  EXPECT_TRUE(result2[1].second);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[1], "one");
  EXPECT_EQ(m2[2], "two");

  s21::map<int, std::string> m3;
  auto result3 = m3.insert_many();

  EXPECT_TRUE(result3.empty());
  EXPECT_TRUE(m3.empty());
}
