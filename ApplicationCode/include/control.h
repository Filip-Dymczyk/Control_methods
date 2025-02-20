// Author : Filip Dymczyk
// Description : Control class handling control methods logic based on user input into the app.

#pragma once
#include <cstdint>
#include <vector>
#include "bang_bang_controller.h"
#include "base_classes/controller_base.h"
#include "base_classes/object_representation_base.h"
#include "base_classes/signal_base.h"
#include "control_system.h"
#include "enums.h"
#include "object_differential_equation_representation.h"
#include "object_state_space_representation.h"
#include "pid.h"
#include "pid_tuner.h"
#include "recursive_linear_regression.h"
#include "signals.h"

class Control
{
    // Default values needed for initialization.
    static constexpr std::size_t ORDER {1u};
    static constexpr double TIME_STEP {0.01};

public:
    Control()
        : _differential_equation_representation_object(TIME_STEP, ORDER),
          _state_space_representation_object(TIME_STEP, ORDER),
          _pid_controller(TIME_STEP),
          _bang_bang_controller(TIME_STEP),
          _heaviside(TIME_STEP),
          _ramp(TIME_STEP),
          _rect(TIME_STEP),
          _sine_wave(TIME_STEP),
          _pulse_wave(TIME_STEP),
          _selected_object(&_differential_equation_representation_object),
          _selected_controller(nullptr),
          _selected_input_signal(&_heaviside),
          _regression(),
          _system(_selected_object, _selected_controller, Control_System::Control_Mode::OPEN_LOOP),
          _tuner(_system, _regression),
          _operation_type(Operation_Type::SIMULATION)
    {
    }

    void
    set_object(
        int order, double time_step, Object_Representation object_representation,
        std::vector<double> const& object_parameters)
    {
        switch(object_representation)
        {
            case Object_Representation::EQUATION:
            {
                _selected_object = &_differential_equation_representation_object;
                break;
            }
            case Object_Representation::STATE_SPACE:
            {
                // TODO: when matrix input will be handled
                // _selected_object = &_state_space_representation_object;
                break;
            }
            default:
                break;
        }
        // If it will be handled like that then input to function will have to take matrices into account and base class
        // as well will have to overload.
        _selected_object->set_order(static_cast<std::size_t>(order));
        _selected_object->set_parameters(object_parameters);
        _selected_object->set_time_step(time_step);
    }

    void
    set_control_mode(Control_Mode control_mode)
    {
        _system.set_control_mode(static_cast<Control_System::Control_Mode>(control_mode));
    }

    void
    set_controller(double time_step, Controller_Type controller_type, std::vector<double> const& controller_parameters)
    {
        switch(controller_type)
        {
            case Controller_Type::BANG_BANG:
            {
                _selected_controller = &_bang_bang_controller;
                break;
            }
            case Controller_Type::PID:
            {
                _selected_controller = &_pid_controller;
                break;
            }
            case Controller_Type::NONE:
            {
                _selected_controller = nullptr;
                return;
            }
            default:
                break;
        }
        _selected_controller->set_time_step(time_step);
        _selected_controller->set_parameters(controller_parameters);
    }

    void
    set_signal(double time_step, Input_Signal input_signal /*, signal parameters missing*/)
    {
        switch(input_signal)
        {
            case Input_Signal::HEAVISIDE:
            {
                _selected_input_signal = &_heaviside;
                break;
            }
            case Input_Signal::RAMP:
            {
                _selected_input_signal = &_ramp;
                break;
            }
            case Input_Signal::RECTANGLE:
            {
                _selected_input_signal = &_rect;
                break;
            }
            case Input_Signal::SINE_WAVE:
            {
                _selected_input_signal = &_sine_wave;
                break;
            }
            case Input_Signal::PULSE_WAVE:
            {
                _selected_input_signal = &_pulse_wave;
                break;
            }
            default:
                break;
        }
        _selected_input_signal->set_time_step(time_step);
    }

    void
    set_operation_type(Operation_Type operation_type)
    {
        _operation_type = operation_type;
    }

    double
    get_time() const
    {
        return _selected_input_signal->time();
    }

    double
    get_setpoint() const
    {
        return _selected_input_signal->get_value();
    }

    double
    get_control_value() const
    {
        return _system.get_control();
    }

    double
    get_object_value() const
    {
        return _system.get_output();
    }

    void
    update()
    {
        _system.update(_selected_input_signal->get_value());
        _selected_input_signal->update();
    }

    Control_System::Control_Mode
    get_control_mode() const
    {
        return _system.get_control_mode();
    }

    void
    reset()
    {
        _selected_object->reset();

        if(_selected_controller != nullptr)
        {
            _selected_controller->reset();
        }

        _selected_input_signal->reset();
    }

private:
    Object_Differential_Equation_Representation _differential_equation_representation_object;
    Object_State_Space_Representation _state_space_representation_object;
    PID _pid_controller;
    Bang_Bang_Controller _bang_bang_controller;
    Heaviside _heaviside;
    Ramp _ramp;
    Rectangle _rect;
    Sine_Wave _sine_wave;
    Pulse_Wave _pulse_wave;

    Object_Representation_Base* _selected_object;
    Controller_Base* _selected_controller;
    Signal_Base* _selected_input_signal;

    Recursive_Linear_Regression _regression;
    Control_System _system;
    Pid_Tuner _tuner;
    Operation_Type _operation_type;
};