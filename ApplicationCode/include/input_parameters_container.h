// Author : Filip Dymczyk
// Description : Dependency handler input parameter container.

#pragma once
#include <cstdint>
#include <vector>
#include "enums.h"

class Input_Parameters_Container
{
    struct Buttons_Inputs
    {
        std::vector<double> object_parameters {1.0, 1.0};
        std::vector<double> controller_parameters {1.0, 1.0, 0.0};
        double simulation_time {1.0};
    };

    struct ComboBoxes_Inputs
    {
        Object_Representation object_representation = Object_Representation::EQUATION;
        Control_Mode control_mode                   = Control_Mode::OPEN_LOOP;
        Controller_Type controller_type             = Controller_Type::NONE;
        Input_Signal input_signal                   = Input_Signal::NONE;
        Operation_Type operation_type               = Operation_Type::SIMULATION;
        double simulation_time_step {0.01};
    };

public:
    void
    set_order(int order)
    {
        _order = order;
    }

    void
    set_object_parameters(std::vector<double> const& object_parameters)
    {
        _button_inputs.object_parameters = object_parameters;
    }

    void
    set_controller_parameters(std::vector<double> const& controller_parameters)
    {
        _button_inputs.controller_parameters = controller_parameters;
    }

    void
    set_simulation_time(double simulation_time)
    {
        _button_inputs.simulation_time = simulation_time;
    }

    void
    set_simulation_time_step(double simulation_time_step)
    {
        _comboboxes_inputs.simulation_time_step = simulation_time_step;
    }

    void
    set_object_representation(Object_Representation const& object_representation)
    {
        _comboboxes_inputs.object_representation = object_representation;
    }

    void
    set_control_mode(Control_Mode const& control_mode)
    {
        _comboboxes_inputs.control_mode = control_mode;
    }

    void
    set_controller_type(Controller_Type const& controller_type)
    {
        _comboboxes_inputs.controller_type = controller_type;
    }

    void
    set_input_signal(Input_Signal const& input_signal)
    {
        _comboboxes_inputs.input_signal = input_signal;
    }

    void
    set_operation_type(Operation_Type const& operation_type)
    {
        _comboboxes_inputs.operation_type = operation_type;
    }

    int
    get_order() const
    {
        return _order;
    }

    std::vector<double> const&
    get_object_parameters() const
    {
        return _button_inputs.object_parameters;
    }

    std::vector<double> const&
    get_controller_parameters() const
    {
        return _button_inputs.controller_parameters;
    }

    double
    get_simulation_time() const
    {
        return _button_inputs.simulation_time;
    }

    double
    get_simulation_time_step() const
    {
        return _comboboxes_inputs.simulation_time_step;
    }

    Object_Representation
    get_object_representation() const
    {
        return _comboboxes_inputs.object_representation;
    }

    Control_Mode
    get_control_mode() const
    {
        return _comboboxes_inputs.control_mode;
    }

    Controller_Type
    get_controller_type() const
    {
        return _comboboxes_inputs.controller_type;
    }

    Input_Signal
    get_input_signal() const
    {
        return _comboboxes_inputs.input_signal;
    }

    Operation_Type
    get_operation_type() const
    {
        return _comboboxes_inputs.operation_type;
    }

private:
    int _order {1};
    Buttons_Inputs _button_inputs {};
    ComboBoxes_Inputs _comboboxes_inputs {};
};