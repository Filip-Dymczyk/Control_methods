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

# Define INTERFACE libraries for headers.
# NOTE: add more if needed.
#-------------------------------------------------
add_library(algebra INTERFACE)
add_library(signals INTERFACE)
#-------------------------------------------------

# Specify directories containing headers.
# NOTE: add more if needed.
#-------------------------------------------------
target_include_directories(algebra INTERFACE ${PROJECT_SOURCE_DIR}/Source)
target_include_directories(signals INTERFACE ${PROJECT_SOURCE_DIR}/Source)
#-------------------------------------------------

# Helper macro to simplify the addition of test executables with libraries.
#-------------------------------------------------
macro(add_test_executable_with_libs test_name test_source libs)
  add_executable(${test_name} ${test_source})
  target_link_libraries(${test_name} GTest::gtest_main ${libs})
  gtest_discover_tests(${test_name})
endmacro()
#-------------------------------------------------

# Add test executables with corresponding defined library.
#-------------------------------------------------
add_test_executable_with_libs(algebra_test Tests/test_suites/algebra_test.cpp algebra)
add_test_executable_with_libs(signals_test Tests/test_suites/signals_test.cpp signals)
#-------------------------------------------------
