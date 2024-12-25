// Author : Filip Dymczyk
// Description : Simulator class connects Control class to Plotter class.

#pragma once

#include "input_parameters_container.h"
#include "control.h"
#include "plotter.h"

class Simulator
{
public:
    void
    update(InputParameterContainer const& input_parameters)
    {
        _simulation_time = input_parameters.get_simulation_time();
        _simulation_time_step = input_parameters.get_simulation_time_step();
        _control.set_object(input_parameters.get_object_representation(), input_parameters.get_object_parameters());
        _control.set_control_mode(input_parameters.get_control_mode());
        _control.set_controller(input_parameters.get_controller_type(), input_parameters.get_controller_parameters());
        _control.set_signal(input_parameters.get_input_signal());
        _control.set_operation_type(input_parameters.get_operation_type());
    }

    void
    run()
    {
        
    }

    void
    show_plot()
    {
        _plotter.plot();
    }
private:
    double _simulation_time {};
    double _simulation_time_step {};
    Control _control;
    Plotter _plotter;
};