#include<gtest/gtest.h>
#include<memory_provider_singleton_template.hpp>

int const TEST_MEMORY_PROVIDER_SIZE = 5;
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