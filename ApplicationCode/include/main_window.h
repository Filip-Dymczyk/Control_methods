// Author : Filip Dymczyk
// Description : Main application window.

#pragma once

#include <QtCore/QString>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QCheckbox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <tuple>
#include "clickable_line_edit.h"
#include "enums.h"
#include "main_widget.h"
#include "simulator.h"

class Main_Window : public QMainWindow
{
    QString const window_title = "Dynamical systems control methods.";

public:
    Main_Window() : _main_widget(new Main_Widget(this)), _simulator(this)
    {
        this->setWindowTitle(window_title);
        this->setCentralWidget(_main_widget);

        this->addToolBar(create_toolbar());
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
    }

private:
    std::tuple<int, int> _center_position {};
    Main_Widget* _main_widget {nullptr};
    Simulator _simulator;

    void
    run_simulation()
    {
        if(!_main_widget->dependency_handler()->get_input_parameters().allowed_to_run())
        {
            QMessageBox::critical(this, "Error", "Some inputs have invalid sizes!");
            return;
        }
        _simulator.update(_main_widget->dependency_handler()->get_input_parameters());
        _simulator.run();
    }

    void
    center()
    {
        if(std::tuple_size<decltype(_center_position)>::value == 2)
        {
            this->move(std::get<0>(_center_position), std::get<1>(_center_position));
        }
    }

    QToolBar*
    create_toolbar()
    {
        QPushButton* run_button = new QPushButton("Run");  // Maybe this will be changed for QAction with and Icon.
        run_button->setToolTip("<p><i>Run the application.</i></p>");
        connect(run_button, &QPushButton::clicked, this, &Main_Window::run_simulation);

        QPushButton* center_button = new QPushButton("Center");
        center_button->setToolTip("<p><i>Center the window.</i></p>");
        connect(center_button, &QPushButton::clicked, this, &Main_Window::center);

        QCheckBox* plot_control_signal_checkbox = new QCheckBox("Plot control signal");
        plot_control_signal_checkbox->setLayoutDirection(Qt::RightToLeft);
        plot_control_signal_checkbox->setToolTip("<p><i>Select to plot control signal.</i></p>");
        plot_control_signal_checkbox->setChecked(false);
        connect(
            plot_control_signal_checkbox, &QCheckBox::stateChanged, _main_widget,
            &Main_Widget::plot_control_signal_changed);

        QCheckBox* measurement_noise_checkbox = new QCheckBox("Enable measurement noise");
        measurement_noise_checkbox->setLayoutDirection(Qt::RightToLeft);
        measurement_noise_checkbox->setToolTip("<p><i>Enable measurement noise simulation.</i></p>");
        measurement_noise_checkbox->setChecked(false);
        connect(
            measurement_noise_checkbox, &QCheckBox::stateChanged, _main_widget, &Main_Widget::enable_measurement_noise);

        ClickableLineEdit* measurement_noise_line_edit = new ClickableLineEdit();
        _main_widget->set_up_line_edit(
            measurement_noise_line_edit, "0.001", "<p><i>Set measurement noise standard deviation.</i></p>");
        measurement_noise_line_edit->setProperty("id", static_cast<int>(LineEdit_ID::MEASUREMENT_NOISE_LINE_EDIT));
        _main_widget->set_line_edit_id(static_cast<int>(LineEdit_ID::MEASUREMENT_NOISE_LINE_EDIT) + 1);

        QFontMetrics const metrics_measurement_noise(measurement_noise_line_edit->font());
        int text_width    = metrics_measurement_noise.horizontalAdvance(measurement_noise_line_edit->text());
        int const padding = 50;
        measurement_noise_line_edit->setFixedWidth(text_width + padding);

        QCheckBox* pid_derivative_filtering_checkbox = new QCheckBox("Enable PID derivative filtering");
        pid_derivative_filtering_checkbox->setLayoutDirection(Qt::RightToLeft);
        pid_derivative_filtering_checkbox->setToolTip("<p><i>Enable derivative input low pass filtering.</i></p>");
        pid_derivative_filtering_checkbox->setChecked(false);
        connect(
            pid_derivative_filtering_checkbox, &QCheckBox::stateChanged, _main_widget,
            &Main_Widget::enable_pid_derivative_filtering);

        ClickableLineEdit* pid_derivative_filtering_coefficient_line_edit = new ClickableLineEdit();
        _main_widget->set_up_line_edit(
            pid_derivative_filtering_coefficient_line_edit, "0.5", "<p><i>Set filtering coefficient.</i></p>");
        pid_derivative_filtering_coefficient_line_edit->setProperty(
            "id", static_cast<int>(LineEdit_ID::PID_DERIVATIVE_FILTERING_COEFFICIENT_LINE_EDIT));
        _main_widget->set_line_edit_id(
            static_cast<int>(LineEdit_ID::PID_DERIVATIVE_FILTERING_COEFFICIENT_LINE_EDIT) + 1);

        QFontMetrics const metrics_pid_derivative_filtering_coefficient {
            pid_derivative_filtering_coefficient_line_edit->font()};
        text_width = metrics_pid_derivative_filtering_coefficient.horizontalAdvance(
            pid_derivative_filtering_coefficient_line_edit->text());
        pid_derivative_filtering_coefficient_line_edit->setFixedWidth(text_width + padding);

        QToolBar* toolbar = new QToolBar();
        toolbar->addWidget(run_button);
        toolbar->addWidget(center_button);
        toolbar->addWidget(plot_control_signal_checkbox);

        toolbar->addWidget(measurement_noise_checkbox);
        QAction* measurement_noise_action = toolbar->addWidget(measurement_noise_line_edit);
        measurement_noise_action->setVisible(false);

        toolbar->addWidget(pid_derivative_filtering_checkbox);
        QAction* pid_derivative_filtering_coefficient_action =
            toolbar->addWidget(pid_derivative_filtering_coefficient_line_edit);
        pid_derivative_filtering_coefficient_action->setVisible(false);

        connect(measurement_noise_checkbox, &QCheckBox::stateChanged, [measurement_noise_action](bool checked) {
            measurement_noise_action->setVisible(checked);
        });
        connect(
            pid_derivative_filtering_checkbox, &QCheckBox::stateChanged,
            [pid_derivative_filtering_coefficient_action](bool checked) {
                pid_derivative_filtering_coefficient_action->setVisible(checked);
            });

        return toolbar;
    }
};