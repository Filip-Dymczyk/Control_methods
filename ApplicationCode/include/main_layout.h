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
    QLabel _representation_label {};
    QComboBox _object_representation_combobox {};
    QLabel _parameters_label {};
    QLineEdit _object_parameters_line_edit {};
    QPushButton _confirm_object_parameters_button {};
    QLabel _control_mode_label {};
    QComboBox _control_mode_combobox {};
    QLabel _controller_type_label {};
    QComboBox _controller_type_combobox {};
    QLabel _controller_parameters_label {};
    QLineEdit _controller_parameters_line_edit {};
    QPushButton _confirm_controller_parameters_button {};
    QLabel _input_signal_label {};
    QComboBox _input_signal_combobox {};
    QLabel _operation_label {};
    QComboBox _operation_combobox {};
    QLabel _simulation_time_label {};
    QLineEdit _simulation_time_line_edit {};
    QPushButton _confirm_simulation_time_button {};
    QComboBox _simulation_step_combobox {};
    QPushButton _run_button {};

    Dependency_Handler _dependency_handler {};

    void
    configure_labels()
    {
        _order_label.setText("Choose the order of dynamical system:");
        _representation_label.setText("Choose the representation of the object to be used:");
        _parameters_label.setText("Enter object parameters divided with semicolons:");
        _control_mode_label.setText("Select control mode:");
        _controller_type_label.setText("Select controller to be used:");
        _controller_parameters_label.setText("Enter controller parameters divided with semicolons:");
        _input_signal_label.setText("Select input signal:");
        _operation_label.setText("Select operation:");
        _simulation_time_label.setText("Enter simulation time:");
    }

    void
    configure_buttons()
    {
        _confirm_controller_parameters_button.setText("Confirm");
        _confirm_simulation_time_button.setText("Confirm");
        _run_button.setText("Run operation");
    }

    void
    configure_comboboxes()
    {
        _object_representation_combobox.addItem("Object equation representation");
        _object_representation_combobox.addItem("Object state space representation");
        _control_mode_combobox.addItem("Open loop");
        _control_mode_combobox.addItem("Closed loop");
        _controller_type_combobox.addItem("No controller");
        _controller_type_combobox.addItem("Bang-Bang controller");
        _controller_type_combobox.addItem("PID");
        _confirm_object_parameters_button.setText("Confirm");
        _input_signal_combobox.addItem("No signal");
        _input_signal_combobox.addItem("Heaviside");
        _input_signal_combobox.addItem("Ramp");
        _input_signal_combobox.addItem("Rectangle");
        _input_signal_combobox.addItem("Sine wave");
        _input_signal_combobox.addItem("Pulse wave");
        _operation_combobox.addItem("Simulation");
        _operation_combobox.addItem("Tuning");

        QList<double> default_simulation_steps = {0.01, 0.001, 0.0001};
        for(double simulation_step: default_simulation_steps)
        {
            _simulation_step_combobox.addItem(QString::number(simulation_step), simulation_step);
        }
    }

    void
    set_widgets_ids()
    {
        _confirm_object_parameters_button.setProperty("id", 0);
        _confirm_controller_parameters_button.setProperty("id", 1);
        _confirm_simulation_time_button.setProperty("id", 2);

        _object_representation_combobox.setProperty("id", 0);
        _control_mode_combobox.setProperty("id", 1);
        _controller_type_combobox.setProperty("id", 2);
        _input_signal_combobox.setProperty("id", 3);
        _operation_combobox.setProperty("id", 4);
    }

    void
    connect_buttons_dependencies()
    {
        connect(&_run_button, QPushButton::clicked, &_dependency_handler, &Dependency_Handler::show_plot_window);
        connect(
            &_confirm_object_parameters_button, &QPushButton::clicked, &_dependency_handler,
            &Dependency_Handler::buttons_clicked_callback);
        connect(
            &_confirm_controller_parameters_button, &QPushButton::clicked, &_dependency_handler,
            &Dependency_Handler::buttons_clicked_callback);
        connect(
            &_confirm_simulation_time_button, &QPushButton::clicked, &_dependency_handler,
            &Dependency_Handler::buttons_clicked_callback);
    }

    void
    connect_comboboxes_dependencies()
    {
        connect(
            &_object_representation_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::comboboxes_callback);
        connect(
            &_control_mode_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::comboboxes_callback);
        connect(
            &_controller_type_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::comboboxes_callback);
        connect(
            &_input_signal_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::comboboxes_callback);
        connect(
            &_operation_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::comboboxes_callback);
        connect(
            &_simulation_step_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), &_dependency_handler,
            &Dependency_Handler::simulation_time_step_callback);
    }

    void
    connect_widgets_dependencies()
    {
        connect(
            &_order_spin_box, QOverload<int>::of(&QSpinBox::valueChanged), &_dependency_handler,
            &Dependency_Handler::order_spinbox_callback);
        connect_buttons_dependencies();
        connect_comboboxes_dependencies();
    }

    void
    set_widgets_names()
    {
        _order_spin_box.setObjectName("order");
        _object_parameters_line_edit.setObjectName("object_parameters");
        _controller_parameters_line_edit.setObjectName("controller_parameters");
        _simulation_time_line_edit.setObjectName("simulation_time");
        _simulation_step_combobox.setObjectName("simulation_step");
    }

    void
    set_line_edits_default_values()
    {
        _object_parameters_line_edit.setText("1.0;1.0");
        _controller_parameters_line_edit.setText("1.0;1.0;0.0");
        _simulation_time_line_edit.setText("1.0");
    }

    void
    configure_widgets()
    {
        _order_spin_box.setRange(1, 10);
        _order_spin_box.setValue(1);

        configure_labels();
        configure_buttons();
        configure_comboboxes();
        set_line_edits_default_values();
        set_widgets_ids();
        set_widgets_names();
        connect_widgets_dependencies();
    }

    void
    add_widgets()
    {
        this->addWidget(&_order_label);
        this->addWidget(&_order_spin_box);
        this->addWidget(&_representation_label);
        this->addWidget(&_object_representation_combobox);
        this->addWidget(&_parameters_label);
        this->addWidget(&_object_parameters_line_edit);
        this->addWidget(&_confirm_object_parameters_button);
        this->addWidget(&_control_mode_label);
        this->addWidget(&_control_mode_combobox);
        this->addWidget(&_controller_type_label);
        this->addWidget(&_controller_type_combobox);
        this->addWidget(&_controller_parameters_label);
        this->addWidget(&_controller_parameters_line_edit);
        this->addWidget(&_confirm_controller_parameters_button);
        this->addWidget(&_input_signal_label);
        this->addWidget(&_input_signal_combobox);
        this->addWidget(&_operation_label);
        this->addWidget(&_operation_combobox);
        this->addWidget(&_simulation_time_label);
        this->addWidget(&_simulation_time_line_edit);
        this->addWidget(&_confirm_simulation_time_button);
        this->addWidget(&_simulation_step_combobox);
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