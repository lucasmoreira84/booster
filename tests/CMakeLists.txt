add_subdirectory(googletest)

add_executable(unit_tests
  source/main.cpp
  source/stack_tests.cpp
  source/memory_provider_singleton_tests.cpp
)

target_link_libraries(unit_tests
  PRIVATE
    booster
    gtest
)
