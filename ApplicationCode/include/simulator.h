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
    static constexpr ControlMode CONTROL_MODE = ControlMode::OPEN_LOOP;
    static constexpr std::uint32_t ORDER {1u}; // Default order value in the app.
     static constexpr double TIME_STEP {0.01}; // Default time_step
public:
    Simulator() : 
            // Components default initialization:
            _diferential_equation_representation_object(TIME_STEP, ORDER), 
            _state_space_representation_object(TIME_STEP, ORDER),
            _pid_controller(TIME_STEP),
            _two_positon_controller(TIME_STEP),
            _heaviside(TIME_STEP, {0.0, 0.0}), // Default values - basically no signal.
            _ramp(TIME_STEP),
            _rect(TIME_STEP),
            _sine_wave(TIME_STEP),
            _pulse_wave(TIME_STEP),
            //-----------------------------------------------------------
            // Default selections based on the application initial state:
            _selected_object(&_diferential_equation_representation_object),
            _selected_controller(&_pid_controller),
            _selected_input_signal(&_heaviside),
            //-----------------------------------------------------------
            // Continous initialization:
            _regression {},
            _system(_selected_object, _selected_controller, CONTROL_MODE),
            _tuner(_system, _regression)
            //-----------------------------------------------------------
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

    RecursiveLinearRegression _regression;
    ControlSystem _system;
    PidTuner _tuner;
};