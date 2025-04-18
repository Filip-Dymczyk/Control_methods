// Author : Filip Dymczyk
// Description : Dependency handler input parameter container.

#pragma once
#include <cstdint>
#include <vector>
#include "base_classes/signal_base.h"
#include "enums.h"

class Input_Parameters_Container
{
    struct LineEdit_Inputs
    {
        std::vector<double> object_parameters {1.0, 1.0};
        std::vector<double> controller_parameters {1.0, 1.0, 0.0};
        double start_time {0.0};
        double scaler {1.0};
        double on_time {0.0};
        double omega {0.0};
        double offset {0.0};
        double duty_cycle {0.0};
        double period {0.0};
        double simulation_time {10.0};
    };

    struct ComboBoxes_Inputs
    {
        Object_Representation object_representation = Object_Representation::EQUATION;
        Control_Mode control_mode                   = Control_Mode::OPEN_LOOP;
        Controller_Type controller_type             = Controller_Type::NONE;
        Input_Signal input_signal                   = Input_Signal::HEAVISIDE;
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
        _line_edit_inputs.object_parameters = object_parameters;
    }

    void
    set_controller_parameters(std::vector<double> const& controller_parameters)
    {
        _line_edit_inputs.controller_parameters = controller_parameters;
    }

    void
    set_start_time(double start_time)
    {
        _line_edit_inputs.start_time = start_time;
    }

    void
    set_scaler(double scaler)
    {
        _line_edit_inputs.scaler = scaler;
    }

    void
    set_on_time(double on_time)
    {
        _line_edit_inputs.on_time = on_time;
    }

    void
    set_omega(double omega)
    {
        _line_edit_inputs.omega = omega;
    }

    void
    set_offset(double offset)
    {
        _line_edit_inputs.offset = offset;
    }

    void
    set_duty_cycle(double duty_cycle)
    {
        _line_edit_inputs.duty_cycle = duty_cycle;
    }

    void
    set_period(double period)
    {
        _line_edit_inputs.period = period;
    }

    void
    set_simulation_time(double simulation_time)
    {
        _line_edit_inputs.simulation_time = simulation_time;
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
        return _line_edit_inputs.object_parameters;
    }

    std::vector<double> const&
    get_controller_parameters() const
    {
        return _line_edit_inputs.controller_parameters;
    }

    double
    get_simulation_time() const
    {
        return _line_edit_inputs.simulation_time;
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

    Signal_Base::Signal_Basic_Parameters
    get_input_signal_basic_parameters() const
    {
        return {_line_edit_inputs.start_time, _line_edit_inputs.scaler};
    }

    std::array<double, 5>
    get_input_signal_advanced_parameters() const
    {
        return {
            _line_edit_inputs.on_time, _line_edit_inputs.omega, _line_edit_inputs.offset, _line_edit_inputs.period,
            _line_edit_inputs.duty_cycle};
    }

    Operation_Type
    get_operation_type() const
    {
        return _comboboxes_inputs.operation_type;
    }

private:
    int _order {1};
    LineEdit_Inputs _line_edit_inputs {};
    ComboBoxes_Inputs _comboboxes_inputs {};
};