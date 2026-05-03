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

find_package(Python3 REQUIRED COMPONENTS Development NumPy)

add_library(test_library STATIC
    src/test_with_plot.cpp)

target_include_directories(test_library PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdParty)

target_include_directories(test_library PUBLIC include)
target_link_libraries(test_library PUBLIC control_logic Python3::Python Python3::NumPy)

# Helper macro to simplify the addition of test executables.
#-------------------------------------------------
macro(add_test_executable test_name test_source)
  add_executable(${test_name} ${test_source})
  target_link_libraries(${test_name} GTest::gtest_main test_library)
  gtest_discover_tests(${test_name})
endmacro()
#-------------------------------------------------

# Add test executables with corresponding defined library.
#-------------------------------------------------
add_test_executable(algebra_test src/algebra_test.cpp)
add_test_executable(signals_test src/signals_test.cpp)
add_test_executable(components_test src/components_test.cpp)
add_test_executable(control_system_with_pid_test src/control_system_with_pid_test.cpp)
add_test_executable(pid_tuning_test src/pid_tuning_test.cpp)
add_test_executable(control_system_with_bang_bang_controller_test src/control_system_with_bang_bang_controller_test.cpp)
add_test_executable(resetting_test src/resetting_test.cpp)
add_test_executable(derivative_filtering_test src/derivative_filtering_test.cpp)
add_test_executable(initial_conditions_setting_test src/initial_conditions_setting_test.cpp)
#-------------------------------------------------
