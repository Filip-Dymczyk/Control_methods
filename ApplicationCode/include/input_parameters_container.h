// Author : Filip Dymczyk
// Description : Dependency handler input parameter container.

#pragma once
#include <cstdint>
#include <vector>

#include "enums.h"

class InputParameterContainer
{
    struct Buttons_Inputs
    {
        bool run_flag {};
        int order {1};
        std::vector<double> object_parameters;
        std::vector<double> controller_parameters;
        double simulation_time;
        double simulation_time_step;
    };

    struct Combo_Boxes_Inputs
    {
        Object_Representation object_representation = Object_Representation::EQUATION;
        Control_Mode control_mode = Control_Mode::OPEN_LOOP;
        Controller_Type controller_type = Controller_Type::NONE;
        Input_Signal input_signal = Input_Signal::NONE;
        Operation_Type operation_type = Operation_Type::SIMULATION;
    };
public:
    void
    set_run_flag(bool run_flag)
    {
        _button_inputs.run_flag = run_flag;
    }

    void
    set_order(int order)
    {
        _button_inputs.order = order;
    }

    void
    set_object_parameters(std::vector<double> const & object_parameters)
    {
        _button_inputs.object_parameters = object_parameters;
    }

    void
    set_controller_parameters(std::vector<double> const & controller_parameters)
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
        _button_inputs.simulation_time_step = simulation_time_step;
    }

    void
    set_object_representation(Object_Representation const & object_representation)
    {
        _combo_boxes_inputs.object_representation = object_representation;
    }
    
    void
    set_control_mode(Control_Mode const & control_mode)
    {
        _combo_boxes_inputs.control_mode = control_mode;
    }

    void 
    set_controller_type(Controller_Type const & controller_type)
    {
        _combo_boxes_inputs.controller_type = controller_type;
    }

    void
    set_input_signal(Input_Signal const & input_signal)
    {
        _combo_boxes_inputs.input_signal = input_signal;
    }

    void
    set_operation_type(Operation_Type const & operation_type)
    {
        _combo_boxes_inputs.operation_type = operation_type;
    }

    int
    get_order() const
    {
        return _button_inputs.order;
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
        return _button_inputs.simulation_time_step;
    }

    Object_Representation
    get_object_representation() const
    {
        return _combo_boxes_inputs.object_representation;
    }

    Control_Mode
    get_control_mode() const
    {
        return _combo_boxes_inputs.control_mode;
    }

    Controller_Type
    get_controller_type() const
    {
        return _combo_boxes_inputs.controller_type;
    }
    
    Input_Signal
    get_input_signal() const
    {
        return _combo_boxes_inputs.input_signal;
    }

    Operation_Type
    get_operation_type() const
    {
        return _combo_boxes_inputs.operation_type;
    }
    
private:
    Buttons_Inputs _button_inputs {};
    Combo_Boxes_Inputs _combo_boxes_inputs {};
};