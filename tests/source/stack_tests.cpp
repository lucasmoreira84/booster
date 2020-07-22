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

TEST(StackTemplate, push_for_empty_stack)
{
  IntStack stack;
  
  stack.push(5);
  EXPECT_EQ(1, stack.getSize());
  ASSERT_EQ(5, stack.getTop());
}

TEST(StackTemplate, push_for_non_empty_stack)
{
  IntStack stack;
  
  stack.push(5);
  EXPECT_EQ(1, stack.getSize());
  ASSERT_EQ(5, stack.getTop());

  stack.push(25);
  EXPECT_EQ(2, stack.getSize());
  ASSERT_EQ(25, stack.getTop());
}

TEST(StackTemplate, push_until_stack_is_full)
{
  IntStack stack;
  
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    stack.push(i);
    EXPECT_EQ(i + 1, stack.getSize());
    ASSERT_EQ(i, stack.getTop());
  }
}

TEST(StackTemplate, push_no_exception_until_stack_is_full)
{
  IntStack stack;
  
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    ASSERT_NO_THROW(stack.push(i));
  }
}

TEST(StackTemplate, push_throw_exception_after_stack_is_full)
{
  IntStack stack;
  
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    stack.push(i);
  }
  ASSERT_ANY_THROW(stack.push(10));
}

TEST(StackTemplate, getTop_empty_stack)
{
  IntStack stack;
  
  ASSERT_ANY_THROW(stack.getTop());
}

TEST(StackTemplate, getTop_no_exception_non_empty_stack)
{
  IntStack stack;
  stack.push(1);
  ASSERT_NO_THROW(stack.getTop());
}

TEST(StackTemplate, getTop_non_empty_stack)
{
  IntStack stack;
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    stack.push(i);
    ASSERT_EQ(i, stack.getTop());
  }
}

TEST(StackTemplate, pop_correct_size)
{
  IntStack stack;
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    stack.push(i);
  }
  int expectedSize = TEST_STACK_SIZE;
  EXPECT_EQ(expectedSize, stack.getSize());
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    stack.pop();
    expectedSize--;
    ASSERT_EQ(expectedSize, stack.getSize());
  }
}

TEST(StackTemplate, pop_correct_top)
{
  IntStack stack;
  int valuesToPush[TEST_STACK_SIZE] = {10, 20, 30, 40, 55};
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    stack.push(valuesToPush[i]);
  }

  int expectedTopIndex = TEST_STACK_SIZE - 1;
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    ASSERT_EQ(valuesToPush[expectedTopIndex], stack.getTop());
    stack.pop();
    expectedTopIndex--;
  }
}

TEST(StackTemplate, clean_full_stack)
{
  IntStack stack;
  for(int i = 0; i < TEST_STACK_SIZE; i++) {
    stack.push(i);
  }
  stack.clean();
  ASSERT_TRUE(stack.isEmpty());
}