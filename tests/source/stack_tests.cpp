#include<gtest/gtest.h>
#include<stack.hpp>

int const TEST_STACK_SIZE = 5;
typedef booster::StackTemplate<int, TEST_STACK_SIZE> IntStack;

TEST(StackTemplate, isEmpty_for_empty_stack)
{
  IntStack stack;
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTemplate, isEmpty_for_non_empty_stack)
{
  IntStack stack;
  stack.push(1);
  ASSERT_FALSE(stack.isEmpty());
}

TEST(StackTemplate, isEmpty_for_full_stack)
{
  IntStack stack;
  int numberOfElementsPushed{0};
  while (numberOfElementsPushed < TEST_STACK_SIZE) {
    stack.push(1);
    numberOfElementsPushed++;
  }

  ASSERT_FALSE(stack.isEmpty());
}

TEST(StackTemplate, isFull_for_empty_stack)
{
  IntStack stack;
  ASSERT_FALSE(stack.isFull());
}

TEST(StackTemplate, isFull_for_non_empty_stack)
{
  IntStack stack;
  stack.push(1);
  ASSERT_FALSE(stack.isFull());
}

TEST(StackTemplate, isFull_for_full_stack)
{
  IntStack stack;
  int numberOfElementsPushed{0};
  while (numberOfElementsPushed < TEST_STACK_SIZE) {
    stack.push(1);
    numberOfElementsPushed++;
  }

  ASSERT_TRUE(stack.isFull());
}