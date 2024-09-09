cmake_minimum_required(VERSION 3.14)
project(CONTROL_METHODS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Define header-only library
add_library(
    algebra INTERFACE
)

target_include_directories(
    algebra INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/algebra
)

add_executable(
  algebra_test
  Tests/test_suites/algebra_test.cpp
)

add_executable(
  rls_test
  Tests/test_suites/rls_test.cpp
)

target_link_libraries(
  algebra_test
  GTest::gtest_main
  algebra
)

target_link_libraries(
  rls_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(algebra_test)
gtest_discover_tests(rls_test)
