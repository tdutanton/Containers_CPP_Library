#include "s21_test.h"

TEST(RedBlackTree, insert_delete_1) {
  s21::RedBlackTree<std::pair<int, int>, int, int> tree;

  tree.insert({1, 1});
  tree.insert({2, 2});
  tree.insert({3, 3});
  tree.insert({4, 4});
  tree.insert({5, 5});
  tree.insert({6, 6});
  tree.insert({7, 7});
  tree.insert({8, 8});
  tree.insert({9, 9});
  tree.insert({10, 10});
  tree.insert({11, 11});
  tree.insert({12, 12});
  tree.insert({13, 13});
  tree.insert({14, 14});
  tree.insert({15, 15});
  tree.insert({16, 16});
  tree.insert({17, 17});
  tree.insert({18, 18});
  tree.insert({19, 19});
  tree.insert({20, 20});
  tree.insert({21, 21});
  tree.insert({22, 22});
  tree.insert({23, 23});
  tree.insert({24, 24});
  tree.insert({25, 25});
  tree.insert({26, 26});
  tree.insert({27, 27});
  tree.insert({28, 28});
  tree.insert({29, 29});
  tree.insert({30, 30});

  tree.erase(11);
  tree.erase(6);
  tree.erase(12);
  tree.erase(22);
  tree.erase(1);
  tree.erase(26);
  tree.erase(30);
  tree.erase(19);
  tree.erase(9);
  tree.erase(18);
  tree.erase(4);
  tree.erase(2);
  tree.erase(15);
  tree.erase(23);
  tree.erase(27);
  tree.erase(24);
  tree.erase(7);
  tree.erase(14);
  tree.erase(21);
  tree.erase(8);
  tree.erase(29);
  tree.erase(5);
  tree.erase(28);
  tree.erase(10);
  tree.erase(13);
  tree.erase(25);
  tree.erase(3);
  tree.erase(17);
  tree.erase(16);
  tree.erase(20);

  EXPECT_EQ(tree.empty(), true);
  EXPECT_EQ(tree.size(), 0);
}

TEST(RedBlackTree, insert_delete_2) {
  s21::RedBlackTree<std::pair<int, int>, int, int> tree;

  tree.insert({1, 1});
  tree.insert({2, 2});
  tree.insert({3, 3});
  tree.insert({4, 4});
  tree.insert({5, 5});
  tree.insert({6, 6});
  tree.insert({7, 7});

  tree.erase(11);
  tree.erase(6);
  tree.erase(12);
  tree.erase(1);
  tree.erase(9);
  tree.erase(18);
  tree.erase(4);
  tree.erase(2);
  tree.erase(7);
  tree.erase(5);
  tree.erase(3);
  tree.erase(17);

  EXPECT_EQ(tree.empty(), true);
  EXPECT_EQ(tree.size(), 0);
}

TEST(RedBlackTree, insert_delete_3) {
  s21::RedBlackTree<std::pair<int, int>, int, int> tree;

  tree.insert({1, 1});
  tree.insert({2, 2});
  tree.insert({3, 3});
  tree.insert({4, 4});
  tree.insert({5, 5});
  tree.insert({6, 6});
  tree.insert({7, 7});

  tree.erase(11);
  tree.erase(6);
  tree.erase(12);
  tree.erase(1);
  tree.erase(9);
  tree.erase(18);
  tree.erase(4);
  tree.erase(2);
  tree.erase(7);
  tree.erase(5);
  tree.erase(3);
  tree.erase(17);

  tree.insert({10, 10});
  tree.insert({11, 11});
  tree.insert({12, 12});
  tree.insert({13, 13});
  tree.insert({14, 14});
  tree.insert({15, 15});

  EXPECT_EQ(tree.empty(), false);
  EXPECT_EQ(tree.size(), 6);
}

TEST(RedBlackTree, clear_1) {
  s21::RedBlackTree<std::pair<int, int>, int, int> tree;
  tree.insert({1, 1});
  tree.insert({2, 2});
  tree.insert({3, 3});
  tree.insert({4, 4});
  tree.insert({5, 5});
  tree.insert({6, 6});
  tree.insert({7, 7});

  tree.clear();
  EXPECT_EQ(tree.empty(), true);
  EXPECT_EQ(tree.size(), 0);
}

TEST(RedBlackTree, clear_2) {
  s21::RedBlackTree<std::pair<int, int>, int, int> tree;

  tree.clear();
  EXPECT_EQ(tree.empty(), true);
  EXPECT_EQ(tree.size(), 0);
}

TEST(RedBlackTree, Iterators) {
  s21::RedBlackTree<std::pair<int, int>, int, int> tree;
  tree.insert({1, 1});
  tree.insert({2, 2});
  tree.insert({3, 3});
  tree.insert({4, 4});
  tree.insert({5, 5});
  tree.insert({6, 6});
  tree.insert({7, 7});

  auto iter = tree.begin();

  EXPECT_EQ(iter->first, 1);
  EXPECT_EQ(iter->second, 1);
  iter++;
  EXPECT_EQ(iter->first, 2);
  EXPECT_EQ(iter->second, 2);
  ++iter;
  EXPECT_EQ(iter->first, 3);
  EXPECT_EQ(iter->second, 3);
  auto iter2 = tree.end();
  iter2--;
  EXPECT_EQ(iter2->first, 7);
  EXPECT_EQ(iter2->second, 7);
  EXPECT_EQ(tree.empty(), false);

  s21::RedBlackTree<std::pair<int, int>, int, int> tree3 = {};
  auto iter3 = tree3.begin();
  EXPECT_EQ(iter3, tree3.end());
  iter3++;
  EXPECT_EQ(iter3, tree3.end());
  iter3--;
  EXPECT_EQ(iter3, tree3.end());
  iter3 = tree3.end();
  ++iter3;
  EXPECT_EQ(iter3, tree3.end());
  --iter3;
  EXPECT_EQ(iter3, tree3.end());

  tree3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}};
  iter3 = tree3.begin();
  EXPECT_EQ(iter3->first, 1);
  EXPECT_EQ(iter3->second, 1);
  iter3--;
  --iter3;
  EXPECT_EQ(iter3, tree3.begin());
  iter3++;
  EXPECT_EQ(iter3->first, 2);
  EXPECT_EQ(iter3->second, 2);
  ++iter3;
  EXPECT_EQ(iter3->first, 3);
  EXPECT_EQ(iter3->second, 3);
  iter3 = tree3.end();
  iter3++;
  ++iter3;
  EXPECT_EQ(iter3, tree3.end());
  iter3--;
  EXPECT_EQ(iter3->first, 7);
  EXPECT_EQ(iter3->second, 7);
  --iter3;
  EXPECT_EQ(iter3->first, 6);
  EXPECT_EQ(iter3->second, 6);
}

TEST(RedBlackTree, merge) {
  s21::RedBlackTree<std::pair<int, int>, int, int> tree;
  tree.insert({29, 29});
  tree.insert({1, 1});
  tree.insert({15, 15});
  tree.insert({24, 24});
  tree.insert({30, 30});
  tree.insert({6, 6});

  s21::RedBlackTree<std::pair<int, int>, int, int> tree2;
  tree2.insert({299, 299});
  tree2.insert({1, 1});
  tree2.insert({55, 55});

  tree.merge(tree2);

  s21::RedBlackTree<std::pair<int, int>, int, int> tree3;
  tree3.insert({29, 29});
  tree3.insert({1, 1});
  tree3.insert({15, 15});
  tree3.insert({24, 24});
  tree3.insert({30, 30});
  tree3.insert({6, 6});
  tree3.insert({299, 299});
  tree3.insert({55, 55});

  EXPECT_EQ(tree.size(), 8);
  EXPECT_EQ(tree2.size(), 1);

  auto it = tree3.begin();
  for (auto iter = tree.begin(); iter != tree.end(); iter++, it++) {
    EXPECT_EQ(*iter, *it);
  }
}