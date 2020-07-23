#ifndef _MEMORY_PROVIDER_SINGLETON_TEMPLATE_
#define _MEMORY_PROVIDER_SINGLETON_TEMPLATE_

#include <memory>
#include <stack_template.hpp>

using namespace std;

namespace booster {
template<class T, int NUMBER_OF_MEMORY_POSITIONS>
class MemoryProviderSingletonTemplate
{
public:
  static MemoryProviderSingletonTemplate<T, NUMBER_OF_MEMORY_POSITIONS> & GetMemoryProviderInstance()
  {
    static MemoryProviderSingletonTemplate<T, NUMBER_OF_MEMORY_POSITIONS> instance;
    return instance;
  }
  
  shared_ptr<T> getNewMemoryPosition() {
    int availablePositionIndex = m_availableIndicesStack.getTop();
    m_availableIndicesStack.pop();
    m_memoryPositions[availablePositionIndex] = MemoryPosition(availablePositionIndex);
    return static_cast<shared_ptr<T>>(&(m_memoryPositions[availablePositionIndex]));
  }

  void clean()
  {
    memset(m_memoryPositions, 0, sizeof(T) * NUMBER_OF_MEMORY_POSITIONS);
    m_availableIndicesStack.clean();
    for(int i = NUMBER_OF_MEMORY_POSITIONS - 1; i >=0; i--) {
      m_availableIndicesStack.push(i);
    }
  }

  int getNumberOfAvailablePositions() { return m_availableIndicesStack.getSize(); }

private:

  MemoryProviderSingletonTemplate()
  : m_memoryPositions()
  , m_availableIndicesStack()
  {
    clean();
  }

  void freePosition(int index) {
    m_availableIndicesStack.push(index);
  }

  friend class Dealocator;

  struct MemoryPosition : public T
  {
    MemoryPosition() = default;
    MemoryPosition(int newIndex)
    : index(newIndex)
    {}

    void operator delete(void * p)
    {
      MemoryPosition * memoryPosition = static_cast<MemoryPosition *>(p);
      MemoryProviderSingletonTemplate<T, NUMBER_OF_MEMORY_POSITIONS>::GetMemoryProviderInstance().freePosition(memoryPosition->index);
    }
    
    int index;
  };

  MemoryPosition m_memoryPositions[NUMBER_OF_MEMORY_POSITIONS];
  StackTemplate<int, NUMBER_OF_MEMORY_POSITIONS> m_availableIndicesStack;
};
}
#endif