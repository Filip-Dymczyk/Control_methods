// Author : Filip Dymczyk 
// Description : Main application window.

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QString>

#include "main_layout.h"
#include "plot_layout.h"

class MainWindow : public QWidget
{
    static constexpr unsigned width = 400;
    static constexpr unsigned height = 800;
    const QString window_title = "Dynamical systems control methods.";
public:
    MainWindow() : _main_layout(this), _plot_layout(this)
    {   
        connect(&_main_layout, &MainLayout::show_plot_layout, this, &MainWindow::show_plot_layout);
        this -> setWindowTitle(window_title);
        this -> setFixedSize(width, height);
        this -> setLayout(&_main_layout);
    }

    void
    show_plot_layout()
    {
        // Update simulator values before -> get the inputs from dependency handler: _main_layout.dependency_handler().inputs().
        _main_layout.dependency_handler().inputs();
        this -> setLayout(&_main_layout);
    }
private:
    MainLayout _main_layout;
    PlotLayout _plot_layout;
};