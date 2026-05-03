cmake_minimum_required(VERSION 3.14)
project(CONTROL_METHODS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(control_logic)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
else()
    add_subdirectory(gui_logic)
    add_subdirectory(main_application)
endif()
