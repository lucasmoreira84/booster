#ifndef _MEMORY_PROVIDER_SINGLETON_TEMPLATE_
#define _MEMORY_PROVIDER_SINGLETON_TEMPLATE_

#include <memory>
#include <stack.hpp>

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
    m_memoryPositions[availablePositionIndex] = DealocationController(availablePositionIndex);
    return static_cast<shared_ptr<T>>(&(m_memoryPositions[availablePositionIndex]));
  }

  void clean()
  {
    memset(m_memoryPositions, 0, sizeof(T) * NUMBER_OF_MEMORY_POSITIONS);
    m_availableIndicesStack.clean();
  }

  int getNumberOfAvailablePositions() { return m_availableIndicesStack.getSize(); }

protected:
  MemoryProviderSingletonTemplate()
  : m_memoryPositions()
  , m_availableIndicesStack()
  {
    clean();
  }

  class DealocationController : public T
  {
  public:
    DealocationController() = default;
    DealocationController(int newIndex, void (*freePosition)(int))
    : index(newIndex)
    , freePosition(freePosition)
    {}

    void operator delete(void * p)
    {
      static_cast<DealocationController *>(p)->freePosition(static_cast<DealocationController *>(p)->index);
    }
    
private:
    int index;
    void (*freePosition)(int);
  };

  void freePosition(int index) {
    m_availableIndicesStack.push(index);
  }

  DealocationController m_memoryPositions[NUMBER_OF_MEMORY_POSITIONS];
  StackTemplate<int, NUMBER_OF_MEMORY_POSITIONS> m_availableIndicesStack;
};
}
#endif