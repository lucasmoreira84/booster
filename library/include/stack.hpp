#include<exception>

#ifndef _STACK_HPP_
#define _STACK_HPP_
namespace booster{
template<class T, int STACK_MAXIMUM_SIZE>
class StackTemplate
{
public:
  StackTemplate()
  : m_stack()
  , m_stackTopIndex(EMPTY_STACK_TOP_INDEX)
  {
    memset(m_stack, 0, sizeof(T) * STACK_MAXIMUM_SIZE);
  }

  void push(T const & newElement)
  {
    if (m_stackTopIndex < FULL_STACK_TOP_INDEX) {
      m_stack[m_stackTopIndex++] = newElement;
    }
    else {
      throw std::exception();
    }
  }

  void pop()
  {
    if (m_stackTopIndex > EMPTY_STACK_TOP_INDEX) {
      m_stackTopIndex--;
    }
  }

  T & getTop()
  {
    if (!isEmpty) {
      return m_stack[m_stackTopIndex];
    }
    else {
      throw std::exception();
    }
  }

  bool isEmpty()
  {
    return m_stackTopIndex == EMPTY_STACK_TOP_INDEX;
  }

  bool isFull()
  {
    return m_stackTopIndex == FULL_STACK_TOP_INDEX;
  }

  int getSize()
  {
    return m_stackTopIndex + 1;
  }
  
protected:
  int const FULL_STACK_TOP_INDEX = STACK_MAXIMUM_SIZE - 1;
  int const EMPTY_STACK_TOP_INDEX = -1;
  int const MAXIMUM_SIZE = STACK_MAXIMUM_SIZE;
  
  T m_stack[STACK_MAXIMUM_SIZE];
  int m_stackTopIndex;
};
}
#endif