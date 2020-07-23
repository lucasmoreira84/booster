#include<gtest/gtest.h>
#include<memory_provider_singleton_template.hpp>

int const TEST_MEMORY_PROVIDER_SIZE = 10;
class Placeholder
{
private:
  int m_placeHolder;
};

typedef booster::MemoryProviderSingletonTemplate<Placeholder, TEST_MEMORY_PROVIDER_SIZE> PlaceholderMemoryProvider;

TEST(MemoryProviderSingletonTemplate, GetMemoryProviderInstance)
{
  PlaceholderMemoryProvider & firstMemoryProvider = PlaceholderMemoryProvider::GetMemoryProviderInstance();
  PlaceholderMemoryProvider & secondMemoryProvider = PlaceholderMemoryProvider::GetMemoryProviderInstance();
  ASSERT_EQ(&firstMemoryProvider, &secondMemoryProvider);
}

TEST(MemoryProviderSingletonTemplate, getNumberOfAvailablePositions_clean_memory_provider)
{
  PlaceholderMemoryProvider & memoryProvider = PlaceholderMemoryProvider::GetMemoryProviderInstance();
  memoryProvider.clean();
  ASSERT_EQ(TEST_MEMORY_PROVIDER_SIZE, memoryProvider.getNumberOfAvailablePositions());
}

TEST(MemoryProviderSingletonTemplate, getNumberOfAvailablePositions_full_memory_provider)
{
  PlaceholderMemoryProvider & memoryProvider = PlaceholderMemoryProvider::GetMemoryProviderInstance();
  memoryProvider.clean();

  shared_ptr<Placeholder> placeHolderPointerList[TEST_MEMORY_PROVIDER_SIZE];
  for (int i = 0; i < TEST_MEMORY_PROVIDER_SIZE; i++) {
    placeHolderPointerList[i] = memoryProvider.getNewMemoryPosition();
    int expectedNumberOfAvailablePositions = TEST_MEMORY_PROVIDER_SIZE - i - 1;
      ASSERT_EQ(expectedNumberOfAvailablePositions, memoryProvider.getNumberOfAvailablePositions());
  }
}

TEST(MemoryProviderSingletonTemplate, getNewMemoryPosition_until_memory_full)
{
  PlaceholderMemoryProvider & memoryProvider = PlaceholderMemoryProvider::GetMemoryProviderInstance();
  memoryProvider.clean();
  
  shared_ptr<Placeholder> placeHolderPointerList[TEST_MEMORY_PROVIDER_SIZE];
  for (int i = 0; i < TEST_MEMORY_PROVIDER_SIZE; i++) {
    placeHolderPointerList[i] = memoryProvider.getNewMemoryPosition();
  }
  ASSERT_EQ(0, memoryProvider.getNumberOfAvailablePositions());

  for (int i = 0; i < TEST_MEMORY_PROVIDER_SIZE; i++) {
    for(int j = 0; j < TEST_MEMORY_PROVIDER_SIZE; j++) {
      if (i != j) {
        ASSERT_TRUE(&placeHolderPointerList[i] != &placeHolderPointerList[j]);
      }
    }
  }
}

TEST(MemoryProviderSingletonTemplate, test_dealocation_after_out_of_scope)
{
  PlaceholderMemoryProvider & memoryProvider = PlaceholderMemoryProvider::GetMemoryProviderInstance();
  memoryProvider.clean();
  {
    shared_ptr<Placeholder> placeHolderPointer;
    EXPECT_EQ(TEST_MEMORY_PROVIDER_SIZE, memoryProvider.getNumberOfAvailablePositions());
    placeHolderPointer = memoryProvider.getNewMemoryPosition();
    EXPECT_EQ(TEST_MEMORY_PROVIDER_SIZE - 1, memoryProvider.getNumberOfAvailablePositions());
  }
  ASSERT_EQ(TEST_MEMORY_PROVIDER_SIZE, memoryProvider.getNumberOfAvailablePositions());
}