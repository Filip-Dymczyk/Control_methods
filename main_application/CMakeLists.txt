add_executable(main main.cpp)

target_compile_options(main PRIVATE
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

target_link_libraries(main PRIVATE control_logic gui_logic)