// Author : Filip Dymczyk
// Description : Control class handling control methods logic based on user input into the app.

#pragma once
#include <cstdint>
#include <vector>

#include "base_classes/object_representation_base.h"
#include "base_classes/controller_base.h"
#include "base_classes/signal_base.h"

#include "object_differential_equation_representation.h"
#include "object_state_space_representation.h"
#include "pid.h"
#include "two_position_controller.h"
#include "signals.h"
#include "control_system.h"
#include "recursive_linear_regression.h"
#include "pid_tuner.h"

#include "enums.h"

class Control
{
    // Default values needed for initialization.
    static constexpr std::uint32_t ORDER {1u};
    static constexpr double TIME_STEP {0.01};
public:
    Control() : 
            _differential_equation_representation_object(TIME_STEP, ORDER), 
            _state_space_representation_object(TIME_STEP, ORDER),
            _pid_controller(TIME_STEP),
            _two_position_controller(TIME_STEP),
            _heaviside(TIME_STEP, {0.0, 0.0}), // Default values - basically no signal.
            _ramp(TIME_STEP),
            _rect(TIME_STEP),
            _sine_wave(TIME_STEP),
            _pulse_wave(TIME_STEP),
            _selected_object(&_differential_equation_representation_object),
            _selected_controller(&_pid_controller),
            _selected_input_signal(&_heaviside),
            _control_mode(ControlMode::OPEN_LOOP),
            _regression{},
            _system(_selected_object, _selected_controller, _control_mode),
            _tuner(_system, _regression),
            _operation_type(Operation_Type::SIMULATION)
            {}

    void
    set_object(int order, Object_Representation object_representation, std::vector<double> object_parameters)
    {
        switch (object_representation)
        {
            case Object_Representation::EQUATION:
            {
                _differential_equation_representation_object.set_order(static_cast<std::size_t>(order));
                _differential_equation_representation_object.set_parameters(object_parameters);
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
    }

    void
    set_control_mode(Control_Mode control_mode)
    {
        _control_mode = static_cast<ControlMode>(control_mode);
    }

    void
    set_controller(Controller_Type controller_type, std::vector<double> controller_parameters)
    {
        switch (controller_type)
        {
            case Controller_Type::BANG_BANG:
            {
                _two_position_controller.set_parameters(controller_parameters);
                _selected_controller = &_two_position_controller;
                break;
            }
            case Controller_Type::PID:
            {
                _pid_controller.set_parameters(controller_parameters);
                _selected_controller = &_pid_controller;
                break;
            }
            // TODO: Handle no controller
            default:
                break;
        }
    }

    void
    set_signal(Input_Signal input_signal/*, signal parameters missing*/)
    {
        switch (input_signal)
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
            }
            // TODO: Handle no signal.
            default:
                break;
        }
    }

    void
    set_operation_type(Operation_Type operation_type)
    {
        _operation_type = operation_type;
    }

private:
    ObjectDifferentialEquationRepresentation _differential_equation_representation_object;
    ObjectStateSpaceRepresentation _state_space_representation_object;
    PID _pid_controller;
    TwoPositionController _two_position_controller;
    Heaviside _heaviside;
    Ramp _ramp;
    Rectangle _rect;
    SineWave _sine_wave;
    PulseWave _pulse_wave;
    
    ObjectRepresentationBase * _selected_object;
    ControllerBase * _selected_controller;
    SignalBase * _selected_input_signal;

    ControlMode _control_mode;
    RecursiveLinearRegression _regression;
    ControlSystem _system;
    PidTuner _tuner;
    Operation_Type _operation_type;
};