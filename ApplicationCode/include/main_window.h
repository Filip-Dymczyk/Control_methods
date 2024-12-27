// Author : Filip Dymczyk 
// Description : Main application window.

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include "main_layout.h"
#include "simulator.h"

class MainWindow : public QWidget
{
    static constexpr unsigned width = 400;
    static constexpr unsigned height = 800;
    QString const window_title = "Dynamical systems control methods.";
public:
    MainWindow() : _main_layout(this), _simulator()
    {   
        this -> setWindowTitle(window_title);
        this -> setFixedSize(width, height);
        this -> setLayout(&_main_layout);
        connect(&_main_layout, &MainLayout::show_plot_window, this, &MainWindow::show_plot_window);
    }  

    void
    show_plot_window()
    {
        _simulator.update(_main_layout.dependency_handler().get_input_parameters());
        _simulator.run();
        _simulator.show_plot();
    }
private:
    MainLayout _main_layout;
    Simulator _simulator;
};