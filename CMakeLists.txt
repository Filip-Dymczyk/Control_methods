# Common configuration.
#-------------------------------------------------
cmake_minimum_required(VERSION 3.14)
project(CONTROL_METHODS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#-------------------------------------------------

# Googletest repository fetching.
#-------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
#-------------------------------------------------

# Enabling testing.
#-------------------------------------------------
enable_testing()
#-------------------------------------------------

# Include directories to search for headers.
#-------------------------------------------------
include_directories(
  "C:\\Users\\User\\AppData\\Local\\Programs\\Python\\Python311\\include"
  "C:\\Users\\User\\AppData\\Local\\Programs\\Python\\Python311\\Lib\\site-packages\\numpy\\core\\include"
  Source
  3rdParty
  Tests
)
#-------------------------------------------------

# Helper macro to simplify the addition of test executables.
#-------------------------------------------------
macro(add_test_executable test_name test_source)
  add_executable(${test_name} ${test_source})
  target_link_libraries(${test_name} GTest::gtest_main)
  gtest_discover_tests(${test_name})
endmacro()
#-------------------------------------------------

# Add test executables with corresponding defined library.
#-------------------------------------------------
add_test_executable(algebra_test Tests/test_suites/algebra_test.cpp)
add_test_executable(signals_test Tests/test_suites/signals_test.cpp)
add_test_executable(components_test Tests/test_suites/components_test.cpp)
#-------------------------------------------------
