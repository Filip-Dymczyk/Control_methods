// Author: Filip Dymczyk
// Description : Tuner class performing PID tuning using RLS.

#pragma once
#include "signals.h"
#include "recursive_linear_regression.h"
#include "control_system.h"

class PidTuner
{
public:
    PidTuner(ControlSystem & control_system, 
            RecursiveLinearRegression const & regression) : 
            _control_system(control_system), 
            _regression(regression) {}

    void
    update(double input)
    {
        _control_system.update(input);
        _regression.update(_control_system.get_x(), _control_system.get_error());
        _control_system.get_controller() -> set_params({_regression.get_coeffs()[0], _regression.get_coeffs()[1], _regression.get_coeffs()[2]});
    }

    double
    get_set_point() const
    {
        return _control_system.get_set_point();
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
    reset()
    {
        _control_system.reset();
        _regression.reset();
    }
private:
    ControlSystem & _control_system;
    RecursiveLinearRegression _regression {};
};