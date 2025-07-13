// Author : Filip Dymczyk
// Description : Simulator class connects Control class to Plotter class.

#pragma once

#include <QtWidgets/QApplication>
#include "control.h"
#include "input_parameters_container.h"
#include "plotter.h"

class Simulator
{
public:
    Simulator(QWidget* parent) : _plotter(parent) {}

    void
    update(Input_Parameters_Container const& input_parameters)
    {
        _simulation_time = input_parameters.get_simulation_time();
        _plotter.set_plot_control_signal(input_parameters.get_plot_control_signal());

        double const simulation_time_step = input_parameters.get_simulation_time_step();
        _control.set_object(
            input_parameters.get_orders(), simulation_time_step, input_parameters.get_object_representation(),
            input_parameters.get_initial_conditions(), input_parameters.get_object_parameters(),
            {input_parameters.get_A_matrix(), input_parameters.get_B_vector(), input_parameters.get_C_vector(),
             input_parameters.get_D()});
        _control.set_control_mode(input_parameters.get_control_mode());

        // Prior to setting the controller - to update it properly.
        if(input_parameters.get_controller_type() == Controller_Type::PID)
        {
            _control.enable_pid_derivative_filtering(input_parameters.get_enable_pid_derivative_filtering());
            _control.set_pid_derivative_filtering_coefficient(
                input_parameters.get_pid_derivative_filtering_coefficient());
        }
        _control.set_controller(
            simulation_time_step, input_parameters.get_controller_type(), input_parameters.get_controller_parameters());
        _control.set_signal(
            simulation_time_step, input_parameters.get_input_signal(),
            input_parameters.get_input_signal_basic_parameters(),
            input_parameters.get_input_signal_advanced_parameters());
        _control.set_operation_type(input_parameters.get_operation_type());
        _control.enable_measurement_noise(input_parameters.get_enable_measurement_noise());
        _control.set_measurement_noise_std(input_parameters.get_measurement_noise_std());
    }

    void
    run()
    {
        reset();
        _plotter.show_chart(_control.get_control_mode(), _simulation_time);
        while(_control.get_time() < _simulation_time)
        {
            _plotter.update(
                _control.get_time(), _control.get_setpoint(), _control.get_control_value(),
                _control.get_object_value());
            _control.update();

            QApplication::processEvents();
        }
    }

private:
    void
    reset()
    {
        _control.reset();
        _plotter.reset();
    }

    double _simulation_time {};
    Control _control {};
    Plotter _plotter;
};