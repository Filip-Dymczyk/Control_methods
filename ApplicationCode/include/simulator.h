// Author : Filip Dymczyk
// Description : Simulator class handling control methods logic based on user input into the app.

#pragma once
#include <cstdint>

// Base classes managing polymorphic approach in selecting currently used components:
#include "base_classes/object_representation_base.h"
#include "base_classes/controller_base.h"
#include "base_classes/signal_base.h"

// Components to be used:
#include "object_differential_equation_representation.h"
#include "object_state_space_representation.h"
#include "pid.h"
#include "two_position_controller.h"
#include "signals.h"
#include "control_system.h"
#include "recursive_linear_regression.h"
#include "pid_tuner.h"

class Simulator
{
    // Default values needed for initialization.
    std::uint32_t _order {1u}; // Default order value in the app.
    double _time_step {0.01}; // Default time_step
public:
    Simulator() : 
            _diferential_equation_representation_object(_time_step, _order), 
            _state_space_representation_object(_time_step, _order),
            _pid_controller(_time_step),
            _two_positon_controller(_time_step),
            _heaviside(_time_step, {0.0, 0.0}), // Default values - basically no signal.
            _ramp(_time_step),
            _rect(_time_step),
            _sine_wave(_time_step),
            _pulse_wave(_time_step),
            _selected_object(&_diferential_equation_representation_object),
            _selected_controller(&_pid_controller),
            _selected_input_signal(&_heaviside)
            {}

private:
    ObjectDifferentialEquationRepresentation _diferential_equation_representation_object;
    ObjectStateSpaceRepresentation _state_space_representation_object;
    PID _pid_controller;
    TwoPositionController _two_positon_controller;
    Heaviside _heaviside;
    Ramp _ramp;
    Rectangle _rect;
    SineWave _sine_wave;
    PulseWave _pulse_wave;

    ObjectRepresentationBase * _selected_object;
    ControllerBase * _selected_controller;
    SignalBase * _selected_input_signal;
};