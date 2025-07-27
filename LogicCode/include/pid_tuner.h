// Author: Filip Dymczyk
// Description : Tuner class performing PID tuning using RLS.

#pragma once
#include "control_system.h"
#include "recursive_linear_regression.h"
#include "signals.h"

class Pid_Tuner
{
public:
    Pid_Tuner(Control_System& control_system, Recursive_Linear_Regression const& regression)
        : _control_system(control_system), _regression(regression)
    {
    }

    void
    update(double input)
    {
        if(_control_system.get_controller() == nullptr)
        {
            assert(false);
        }

        _control_system.update(input);
        _regression.update(_control_system.get_x(), _control_system.get_error());
        _control_system.get_controller()->set_parameters(
            {_regression.get_coefficients()[0], _regression.get_coefficients()[1], _regression.get_coefficients()[2]});
    }

    double
    get_output() const
    {
        return _control_system.get_output();
    }

    double
    get_control() const
    {
        return _control_system.get_control();
    }

    void
    set_initial_pid_parameters(std::array<double, 3> pid_parameters)
    {
        _regression.set_initial_coefficients(pid_parameters);
    }

    void
    reset()
    {
        _control_system.reset();
        _regression.reset();
    }

private:
    Control_System& _control_system;
    Recursive_Linear_Regression _regression {};
};