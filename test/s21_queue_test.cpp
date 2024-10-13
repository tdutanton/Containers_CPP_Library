#include "s21_test.h"

using namespace std;

TEST(Constructor_queue, Default) {
  s21::queue<int> que;
  ASSERT_EQ(que.size(), 0);
}

TEST(Constructor_queue, init_list) {
  s21::queue<int> que = {1, 2, 3, 4};
  ASSERT_EQ(que.size(), 4);
}

TEST(Constructor_queue, Copy) {
  s21::queue<int> que = {1, 2, 3, 4};
  s21::queue<int> que2(que);

  ASSERT_EQ(que2.size(), 4);
}

TEST(Constructor_queue, Move) {
  s21::queue<int> que = {1, 2, 3, 4};
  s21::queue<int> que2(std::move(que));

  ASSERT_EQ(que.size(), 0);
}

TEST(Constructor_queue, assignment_operator_for_moving_object) {
  s21::queue<int> que;
  que = s21::queue<int>{1, 2, 34, 5};

  ASSERT_EQ(que.size(), 4);
}

TEST(Method_queue, empty1) {
  s21::queue<int> que;
  que = s21::queue<int>{1, 2, 34, 5};

  ASSERT_EQ(que.empty(), 0);
}

TEST(Method_queue, empty2) {
  s21::queue<int> que;

  ASSERT_EQ(que.empty(), 1);
}

TEST(Method_queue, front) {
  s21::queue<int> que = {21, 2, 3, 15};

  ASSERT_EQ(que.front(), 21);
}

TEST(Method_queue, back) {
  s21::queue<int> que = {21, 2, 3, 15};

  ASSERT_EQ(que.back(), 15);
}

TEST(Method_queue, push) {
  s21::queue<int> que = {21, 2, 3, 15};
  que.push(123);

  ASSERT_EQ(que.back(), 123);
}

TEST(Method_queue, pop) {
  s21::queue<int> que = {21, 2, 3, 15};
  que.pop();

  ASSERT_EQ(que.front(), 2);
}

TEST(Method_queue, swap) {
  s21::queue<int> que1 = {1, 2, 3, 4};
  s21::queue<int> que2 = {7, 8, 2, 48};

  que1.swap(que2);

  ASSERT_EQ(que1.front(), 7);
}

TEST(Method_queue, insert_many_back1) {
  s21::queue<int> que;

  que.insert_many_back(1, 2, 3, 4);

  ASSERT_EQ(que.size(), 4);
}

TEST(Method_queue, insert_many_back2) {
  s21::queue<int> que;

  que.insert_many_back(15, 123, 234);

  ASSERT_EQ(que.front(), 15);
  ASSERT_EQ(que.back(), 234);
}