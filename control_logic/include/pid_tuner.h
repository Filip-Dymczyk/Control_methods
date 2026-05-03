// Author: Filip Dymczyk
// Description : Tuner class performing PID tuning using RLS.

#pragma once
#include "control_system.h"
#include "recursive_linear_regression.h"

class Pid_Tuner
{
public:
    Pid_Tuner(Control_System& control_system, Recursive_Linear_Regression const& regression);

    void
    update(double input);

    double
    get_output() const;

    double
    get_control() const;

    void
    set_initial_pid_parameters(std::array<double, 3> pid_parameters);

    void
    set_RLS_forgetting_factor(double forgetting_factor);

    void
    reset();

private:
    Control_System& m_control_system;
    Recursive_Linear_Regression m_regression {};
};