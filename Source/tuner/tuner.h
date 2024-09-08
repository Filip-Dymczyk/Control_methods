// Author: Filip Dymczyk
// Description : Tuner class performing PID tuning using RLS.

#pragma once
#include "signals/signals.h"

template<typename ControlSystemT, typename RegressionT>
class Tuner
{
public:
    Tuner(Signal * signal, ControlSystemT & control_system, RegressionT const & regression) : _signal(signal), _control_system(control_system), _regression(regression) {}

    void
    update()
    {
        _control_system.update(_signal -> get_value());
        _signal -> update();
        _regression.update(_control_system.get_x(), _control_system.get_error());
        _control_system.set_pid_params(_regression.get_coeffs());
    }

    double 
    get_time() const
    {
        return _signal -> time();
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
private:
    Signal * _signal {};
    ControlSystemT & _control_system {};
    RegressionT _regression {};
};