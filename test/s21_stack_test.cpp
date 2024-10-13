#include "s21_test.h"

TEST(Constructor_stack, Default) {
  s21::stack<int> stack;
  ASSERT_EQ(stack.empty(), 1);
}

TEST(Constructor_stack, init_list) {
  s21::stack<int> stack = {1, 2, 3};
  ASSERT_EQ(stack.top(), 1);
}

TEST(Constructor_stack, Copy) {
  s21::stack<int> stack;

  stack.push(12);
  stack.push(13);
  stack.push(14);

  s21::stack<int> stack_2(stack);

  ASSERT_EQ(stack_2.top(), 14);
}

TEST(Constructor_stack, Move) {
  s21::stack<int> stack;

  stack.push(12);
  stack.push(13);
  stack.push(14);

  s21::stack<int> stack_2(std::move(stack));

  ASSERT_EQ(stack_2.top(), 14);
  ASSERT_EQ(stack.empty(), 1);
}

TEST(Constructor_stack, assignment_operator_for_moving_object) {
  s21::stack<int> stack;
  stack = s21::stack<int>{1, 2, 34, 5};

  ASSERT_EQ(stack.top(), 1);
}

TEST(Stack_methods, push_) {
  s21::stack<int> stack;

  stack.push(15);

  ASSERT_EQ(stack.size(), 1);
}

TEST(Stack_methods, top_1) {
  s21::stack<int> stack;

  stack.push(15);
  stack.top();

  ASSERT_EQ(stack.top(), 15);
}

TEST(Stack_methods, top_2) {
  s21::stack<int> stack;

  stack.push(15);
  stack.push(1);
  stack.push(2);

  stack.top();

  ASSERT_EQ(stack.top(), 2);
}

TEST(Stack_methods, empty_1) {
  s21::stack<int> stack;

  ASSERT_EQ(stack.empty(), 1);
}

TEST(Stack_methods, empty_2) {
  s21::stack<int> stack;

  stack.push(12);

  ASSERT_EQ(stack.empty(), 0);
}

TEST(Stack_methods, pop_1) {
  s21::stack<int> stack;

  stack.push(12);
  stack.pop();

  ASSERT_EQ(stack.empty(), 1);
}

TEST(Stack_methods, pop_2) {
  s21::stack<int> stack;

  stack.push(12);
  stack.push(13);
  stack.push(14);
  stack.push(1);

  stack.pop();
  ASSERT_EQ(stack.top(), 14);
}

TEST(Stack_methods, swap) {
  s21::stack<int> stack1 = {1, 2, 3, 4};
  s21::stack<int> stack2 = {7, 8, 2, 48};

  stack1.swap(stack2);

  ASSERT_EQ(stack1.top(), 7);
}

TEST(Method_stack, insert_many_back1) {
  s21::stack<int> stack;

  stack.insert_many_back(1, 2, 3, 4);

  ASSERT_EQ(stack.size(), 4);
}

TEST(Method_stack, insert_many_back2) {
  s21::stack<int> stack;

  stack.insert_many_back(15, 123, 234);

  ASSERT_EQ(stack.top(), 15);
}