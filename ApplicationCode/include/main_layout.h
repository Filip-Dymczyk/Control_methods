// Author : Filip Dymczyk
// Description : Main application window layout.

#pragma once

#include <QtCore/QObject>
#include <QtCore/Qt>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dependency_handler.h"

class Main_Layout : public QVBoxLayout
{
    Q_OBJECT

public:
    Main_Layout(QWidget* parent) : QVBoxLayout(parent)
    {
        connect(&_dependency_handler, &Dependency_Handler::show_plot_window, this, &Main_Layout::show_plot_window);
        configure_widgets();
        add_widgets();
        set_alignment_and_spacing();
    }

    Dependency_Handler const&
    dependency_handler() const
    {
        return _dependency_handler;
    }

private:
    QLabel _order_label {};
    QSpinBox _order_spin_box {};
    QPushButton _order_confirm_button {};
    QLabel _representation_label {};
    QComboBox _object_representation_combo_box {};
    QLabel _parameters_label {};
    QLineEdit _object_parameters_line_edit {};
    QPushButton _confirm_object_parameters_button {};
    QLabel _control_mode_label {};
    QComboBox _control_mode_combo_box {};
    QLabel _controller_type_label {};
    QComboBox _controller_type_combo_box {};
    QLabel _controller_parameters_label {};
    QLineEdit _controller_parameters_line_edit {};
    QPushButton _confirm_controller_parameters_button {};
    QLabel _input_signal_label {};
    QComboBox _input_signal_combo_box {};
    QLabel _operation_label {};
    QComboBox _operation_combo_box {};
    QLabel _simulation_parameters_label {};
    QLineEdit _simulation_time_line_edit {};
    QLineEdit _simulation_step_line_edit {};
    QPushButton _confirm_simulation_parameters_button {};
    QPushButton _run_button {};

    Dependency_Handler _dependency_handler {};

    void
    set_widgets_ids()
    {
        _order_confirm_button.setProperty("id", 0);
        _confirm_object_parameters_button.setProperty("id", 1);
        _confirm_controller_parameters_button.setProperty("id", 2);
        _confirm_simulation_parameters_button.setProperty("id", 3);
        _run_button.setProperty("id", 4);

        _object_representation_combo_box.setProperty("id", 0);
        _control_mode_combo_box.setProperty("id", 1);
        _controller_type_combo_box.setProperty("id", 2);
        _input_signal_combo_box.setProperty("id", 3);
        _operation_combo_box.setProperty("id", 4);
    }

    void
    connect_widgets_dependencies()
    {
        connect(
            &_order_confirm_button, &QPushButton::clicked, &_dependency_handler,
            &Dependency_Handler::buttons_clicked_callback);
        connect(
            &_confirm_object_parameters_button, &QPushButton::clicked, &_dependency_handler,
            &Dependency_Handler::buttons_clicked_callback);
        connect(
            &_confirm_controller_parameters_button, &QPushButton::clicked, &_dependency_handler,
            &Dependency_Handler::buttons_clicked_callback);
        connect(
            &_confirm_simulation_parameters_button, &QPushButton::clicked, &_dependency_handler,
            &Dependency_Handler::buttons_clicked_callback);
        connect(
            &_run_button, &QPushButton::clicked, &_dependency_handler, &Dependency_Handler::buttons_clicked_callback);

        connect(
            &_object_representation_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged),
            &_dependency_handler, &Dependency_Handler::combo_boxes_callback);
        connect(
            &_control_mode_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::combo_boxes_callback);
        connect(
            &_controller_type_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::combo_boxes_callback);
        connect(
            &_input_signal_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::combo_boxes_callback);
        connect(
            &_operation_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::combo_boxes_callback);
    }

    void
    set_widgets_names()
    {
        _order_spin_box.setObjectName("order");
        _object_parameters_line_edit.setObjectName("object_parameters");
        _controller_parameters_line_edit.setObjectName("controller_parameters");
        _simulation_time_line_edit.setObjectName("simulation_time");
        _simulation_step_line_edit.setObjectName("simulation_step");
    }

    void
    set_default_values()
    {
        _object_parameters_line_edit.setText("1.0;1.0");
        _controller_parameters_line_edit.setText("1.0;1.0;0.0");
        _simulation_time_line_edit.setText("1.0");
        _simulation_step_line_edit.setText("0.01");
    }

    void
    configure_widgets()
    {
        _order_label.setText("Choose the order of dynamical system:");
        _order_spin_box.setRange(1, 10);
        _order_spin_box.setValue(1);
        _order_confirm_button.setText("Confirm");
        _representation_label.setText("Choose the representation of the object to be used:");
        _object_representation_combo_box.addItem("Object equation representation");
        _object_representation_combo_box.addItem("Object state space representation");
        _parameters_label.setText("Enter object parameters divided with semicolons:");
        _confirm_object_parameters_button.setText("Confirm");
        _control_mode_label.setText("Select control mode:");
        _control_mode_combo_box.addItem("Open loop");
        _control_mode_combo_box.addItem("Closed loop");
        _controller_type_label.setText("Select controller to be used:");
        _controller_type_combo_box.addItem("No controller");
        _controller_type_combo_box.addItem("Bang-Bang controller");
        _controller_type_combo_box.addItem("PID");
        _controller_parameters_label.setText("Enter controller parameters divided with semicolons:");
        _confirm_controller_parameters_button.setText("Confirm");
        _input_signal_label.setText("Select input signal:");
        _input_signal_combo_box.addItem("No signal");
        _input_signal_combo_box.addItem("Heaviside");
        _input_signal_combo_box.addItem("Ramp");
        _input_signal_combo_box.addItem("Rectangle");
        _input_signal_combo_box.addItem("Sine wave");
        _input_signal_combo_box.addItem("Pulse wave");
        _operation_label.setText("Select operation:");
        _operation_combo_box.addItem("Simulation");
        _operation_combo_box.addItem("Tuning");
        _simulation_parameters_label.setText("Enter simulation parameters:");
        _confirm_simulation_parameters_button.setText("Confirm");
        _run_button.setText("Run operation");

        set_widgets_ids();
        connect_widgets_dependencies();
        set_widgets_names();
        set_default_values();
    }

    void
    add_widgets()
    {
        this->addWidget(&_order_label);
        this->addWidget(&_order_spin_box);
        this->addWidget(&_order_confirm_button);
        this->addWidget(&_representation_label);
        this->addWidget(&_object_representation_combo_box);
        this->addWidget(&_parameters_label);
        this->addWidget(&_object_parameters_line_edit);
        this->addWidget(&_confirm_object_parameters_button);
        this->addWidget(&_control_mode_label);
        this->addWidget(&_control_mode_combo_box);
        this->addWidget(&_controller_type_label);
        this->addWidget(&_controller_type_combo_box);
        this->addWidget(&_controller_parameters_label);
        this->addWidget(&_controller_parameters_line_edit);
        this->addWidget(&_confirm_controller_parameters_button);
        this->addWidget(&_input_signal_label);
        this->addWidget(&_input_signal_combo_box);
        this->addWidget(&_operation_label);
        this->addWidget(&_operation_combo_box);
        this->addWidget(&_simulation_parameters_label);
        this->addWidget(&_simulation_time_line_edit);
        this->addWidget(&_simulation_step_line_edit);
        this->addWidget(&_confirm_simulation_parameters_button);
        this->addWidget(&_run_button);
    }

    void
    set_alignment_and_spacing()
    {
        this->setAlignment(Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignHCenter);
        this->setSpacing(13);
    }

Q_SIGNALS:
    void
    show_plot_window();
};