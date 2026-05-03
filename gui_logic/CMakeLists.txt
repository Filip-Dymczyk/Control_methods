find_package(Qt6 REQUIRED COMPONENTS Widgets Core Charts)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC_VERBOSE ON)

add_library(gui_logic STATIC
    src/application.cpp
    src/control.cpp
    src/dependency_handler.cpp
    src/inputs_parser.cpp
    src/main_widget.cpp
    src/main_window.cpp
    src/plotter.cpp
    src/simulator.cpp
    
    # For Qt .moc compilation 
    include/main_widget.h
    include/main_window.h
    include/dependency_handler.h
    include/inputs_parser.h
    include/plotter.h
    include/simulator.h
    include/clickable_line_edit.h)

target_include_directories(gui_logic PUBLIC include)

target_link_libraries(gui_logic PUBLIC 
    control_logic
    Qt6::Widgets
    Qt6::Core
    Qt6::Charts)
