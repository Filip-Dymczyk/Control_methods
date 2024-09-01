// Author: Filip Dymczyk
// Description : Tuner class performing PID tuning using RLS.

#pragma once
#include "signals/signals.h"

template<typename ControlSystemT, typename RegressionT>
class Tuner
{
public:
    Tuner(ControlSystemT const & control_system, RegressionT const & regression) : _control_system(control_system), _regression(regression) {}

    void
    update(Signal* signal)
    {
        _control_system.update(signal -> get_value());


        signal.update()
    }
private:
    ControlSystemT & _control_system {};
    RegressionT _regression {};
};