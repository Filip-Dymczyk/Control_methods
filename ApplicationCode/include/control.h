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
    static constexpr std::size_t ORDER {2u};
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
          _selected_object(nullptr),
          _selected_controller(nullptr),
          _selected_input_signal(std::make_unique<Heaviside>(_heaviside)),
          _regression(),
          _system(_selected_object, Control_System::Control_Mode::OPEN_LOOP),
          _tuner(_system, _regression),
          _operation_type(Operation_Type::SIMULATION)
    {
    }

    void
    set_object(
        std::vector<std::size_t> orders, double time_step, Object_Representation object_representation,
        std::vector<double> const& object_parameters, Object_Representation_Base::State_Space_Matrices const& matrices)
    {
        switch(object_representation)
        {
            case Object_Representation::EQUATION:
            {
                _selected_object = std::make_shared<Object_Differential_Equation_Representation>(
                    _differential_equation_representation_object);
                if(_selected_object != nullptr)
                {
                    _selected_object->set_order(orders[static_cast<std::size_t>(
                        Object_Representation::EQUATION)]);  // Order needs to be set prior to setting parameters.
                    _selected_object->set_parameters(object_parameters);
                }
                break;
            }
            case Object_Representation::STATE_SPACE:
            {
                _selected_object =
                    std::make_shared<Object_State_Space_Representation>(_state_space_representation_object);
                if(_selected_object != nullptr)
                {
                    _selected_object->set_order(orders[static_cast<std::size_t>(
                        Object_Representation::STATE_SPACE)]);  // Order needs to be set prior to setting matrices.
                    _selected_object->set_parameters(matrices);
                }
                break;
            }
            default:
                break;
        }
        if(_selected_object != nullptr)
        {
            _selected_object->set_time_step(time_step);
            _system.set_object(_selected_object);
        }
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
                _selected_controller = std::make_shared<Bang_Bang_Controller>(_bang_bang_controller);
                break;
            }
            case Controller_Type::PID:
            {
                _selected_controller = std::make_shared<PID>(_pid_controller);
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

        if(_selected_controller != nullptr)
        {
            _selected_controller->set_time_step(time_step);
            _selected_controller->set_parameters(controller_parameters);
            _system.set_controller(_selected_controller);
        }
    }

    void
    set_signal(
        double time_step, Input_Signal input_signal,
        Signal_Base::Signal_Basic_Parameters const& signal_basic_parameters,
        std::array<double, 5> const& advanced_parameters)
    {
        switch(input_signal)
        {
            case Input_Signal::HEAVISIDE:
            {
                _selected_input_signal = std::make_unique<Heaviside>(_heaviside);
                break;
            }
            case Input_Signal::RAMP:
            {
                _selected_input_signal = std::make_unique<Ramp>(_ramp);
                break;
            }
            case Input_Signal::RECTANGLE:
            {
                _rect.set_on_time(
                    advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::ON_TIME)));
                _selected_input_signal = std::make_unique<Rectangle>(_rect);
                break;
            }
            case Input_Signal::SINE_WAVE:
            {
                _sine_wave.set_omega(
                    advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::OMEGA)));
                _sine_wave.set_offset(
                    advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::OFFSET)));
                _selected_input_signal = std::make_unique<Sine_Wave>(_sine_wave);
                break;
            }
            case Input_Signal::PULSE_WAVE:
            {
                _pulse_wave.set_period(
                    advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::PERIOD)));
                _pulse_wave.set_duty_cycle(
                    advanced_parameters.at(static_cast<std::size_t>(Advanced_Input_Signal_Parameters::DUTY_CYCLE)));
                _selected_input_signal = std::make_unique<Pulse_Wave>(_pulse_wave);
                break;
            }
            default:
                break;
        }

        if(_selected_input_signal != nullptr)
        {
            _selected_input_signal->set_time_step(time_step);
            _selected_input_signal->set_parameters(signal_basic_parameters);
        }
    }

    void
    set_operation_type(Operation_Type operation_type)
    {
        _operation_type = operation_type;
    }

    void
    enable_measurement_noise(bool enable)
    {
        if(_selected_object != nullptr)
        {
            _selected_object->enable_measurement_noise(enable);
        }
    }

    void
    set_measurement_noise_std(double measurement_noise_std)
    {
        if(_selected_object != nullptr)
        {
            _selected_object->set_measurement_noise_std(measurement_noise_std);
        }
    }

    void
    enable_pid_derivative_filtering(bool enable)
    {
        _pid_controller.enable_derivative_filtering(enable);
    }

    void
    set_pid_derivative_filtering_coefficient(double filtering_coefficient)
    {
        _pid_controller.set_derivative_filtering_coefficient(filtering_coefficient);
    }

    double
    get_time() const
    {
        if(_selected_input_signal != nullptr)
        {
            return _selected_input_signal->time();
        }
        return 0.0;
    }

    double
    get_setpoint() const
    {
        if(_selected_input_signal != nullptr)
        {
            return _selected_input_signal->get_value();
        }
        return 0.0;
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
        if(_selected_input_signal == nullptr)
        {
            assert(false);
            return;
        }
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
        if(_selected_object != nullptr)
        {
            _selected_object->reset();
        }

        if(_selected_controller != nullptr)
        {
            _selected_controller->reset();
        }

        if(_selected_input_signal != nullptr)
        {
            _selected_input_signal->reset();
        }
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

    std::shared_ptr<Object_Representation_Base> _selected_object;
    std::shared_ptr<Controller_Base> _selected_controller;
    std::unique_ptr<Signal_Base> _selected_input_signal;

    Recursive_Linear_Regression _regression;
    Control_System _system;
    Pid_Tuner _tuner;
    Operation_Type _operation_type;
};