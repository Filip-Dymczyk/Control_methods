// Author : Filip Dymczyk
// Description : Main application window.

#pragma once

#include <QtCore/QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
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

        QPushButton* run_button = new QPushButton("Run");
        connect(run_button, &QPushButton::clicked, this, &Main_Window::show_plot_window);

        QToolBar* toolbar = new QToolBar();
        toolbar->addWidget(run_button);

        this->addToolBar(toolbar);
    }

private:
    Main_Widget* _main_widget {nullptr};
    Simulator _simulator;

    void
    show_plot_window()
    {
        _simulator.update(_main_widget->dependency_handler()->get_input_parameters());
        _simulator.run();
        _simulator.show_plot();
    }
};