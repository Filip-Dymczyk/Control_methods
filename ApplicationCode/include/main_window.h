// Author : Filip Dymczyk
// Description : Main application window.

#pragma once

#include <QtCore/QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <tuple>
#include "main_widget.h"
#include "simulator.h"

class Main_Window : public QMainWindow
{
    QString const window_title = "Dynamical systems control methods.";

public:
    Main_Window() : _main_widget(new Main_Widget(this)), _simulator()
    {
        this->setWindowTitle(window_title);
        this->setCentralWidget(_main_widget);

        QPushButton* run_button = new QPushButton("Run");  // Maybe this will be changed for QAction with and Icon.
        run_button->setToolTip("<p><i>Run the application.</i></p>");
        connect(run_button, &QPushButton::clicked, this, &Main_Window::show_plot_window);

        QPushButton* center_button = new QPushButton("Center");
        center_button->setToolTip("<p><i>Center the window.</i></p>");
        connect(center_button, &QPushButton::clicked, this, &Main_Window::center);

        QToolBar* toolbar = new QToolBar();
        toolbar->addWidget(run_button);
        toolbar->addWidget(center_button);

        this->addToolBar(toolbar);
    }

    void
    centralize()
    {
        QRect const screen_geometry = this->screen()->availableGeometry();
        QRect const window_geometry = this->frameGeometry();

        int const x      = screen_geometry.center().x() - (window_geometry.width() / 2);
        int const y      = screen_geometry.center().y() - (window_geometry.height() / 2);
        _center_position = std::make_tuple(x, y);

        this->move(x, y);
        this->setFixedSize(this->size());
    }

private:
    std::tuple<int, int> _center_position {};
    Main_Widget* _main_widget {nullptr};
    Simulator _simulator;

    void
    show_plot_window()
    {
        _simulator.update(_main_widget->dependency_handler()->get_input_parameters());
        _simulator.run();
        _simulator.show_plot();
    }

    void
    center()
    {
        if(std::tuple_size<decltype(_center_position)>::value == 2)
        {
            this->move(std::get<0>(_center_position), std::get<1>(_center_position));
        }
    }
};