
add_library(control_logic STATIC
    src/bang_bang_controller.cpp
    src/control_system.cpp
    src/derivative.cpp
    src/integrator.cpp
    src/object_differential_equation_representation.cpp
    src/object_state_space_representation.cpp
    src/pid_tuner.cpp
    src/pid.cpp
    src/recursive_linear_regression.cpp
    src/state.cpp)

target_include_directories(control_logic PUBLIC include)