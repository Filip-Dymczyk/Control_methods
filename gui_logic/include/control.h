// Author : Filip Dymczyk
// Description : Control class handling control methods logic based on user input into the app.

#pragma once
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
    Control();

    void
    set_object(
        std::vector<std::size_t> orders, double time_step, Object_Representation object_representation,
        std::vector<double> const& initial_conditions, std::vector<double> const& object_parameters,
        double control_signal_scaler, Object_Representation_Base::State_Space_Matrices const& matrices);

    void
    set_control_mode(Control_Mode control_mode);

    void
    set_controller(double time_step, Controller_Type controller_type, std::vector<double> const& controller_parameters);

    void
    set_signal(
        double time_step, Input_Signal input_signal,
        Signal_Base::Signal_Basic_Parameters const& signal_basic_parameters,
        std::array<double, 5> const& advanced_parameters);

    void
    set_operation_type(Operation_Type operation_type);

    void
    enable_measurement_noise(bool enable);

    void
    set_measurement_noise_std(double measurement_noise_std);

    void
    set_RLS_forgetting_factor(double forgetting_factor);

    void
    enable_pid_derivative_filtering(bool enable);

    void
    set_pid_derivative_filtering_coefficient(double filtering_coefficient);

    double
    get_time() const;

    double
    get_setpoint() const;

    double
    get_control_value() const;

    double
    get_object_value() const;

    void
    update();

    Control_System::Control_Mode
    get_control_mode() const;

    Operation_Type
    get_operation_type() const;

    std::array<double, 3>
    get_pid_parameters() const;

    void
    reset();

private:
    Object_Differential_Equation_Representation m_differential_equation_representation_object;
    Object_State_Space_Representation m_state_space_representation_object;
    PID m_pid_controller;
    Bang_Bang_Controller m_bang_bang_controller;
    Heaviside m_heaviside;
    Ramp m_ramp;
    Rectangle m_rect;
    Sine_Wave m_sine_wave;
    Pulse_Wave m_pulse_wave;
    No_Signal m_no_signal;

    Object_Representation_Base* m_selected_object;
    Controller_Base* m_selected_controller;
    Signal_Base* m_selected_input_signal;

    Recursive_Linear_Regression m_regression;
    Control_System m_system;
    Pid_Tuner m_tuner;
    Operation_Type m_operation_type;
};