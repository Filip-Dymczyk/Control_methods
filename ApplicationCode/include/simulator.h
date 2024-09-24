// Author : Filip Dymczyk
// Description : Simulator class handling control methods logic based on user input into the app.

#pragma once

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
public:
    Simulator() {}

private:



    ObjectRepresentationBase * _selected_object;
    ControllerBase * _selected_controller;
    SignalBase * _selected_input_signal;
};