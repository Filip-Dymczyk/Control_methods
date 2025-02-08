// Author: Filip Dymczyk
// Description : Base class for signals.

#pragma once
#include "integrator.h"

class Signal_Base
{
public:
    struct Signal_Basic_Parameters
    {
        double start_time {};
        double scaler {1.0};
    };

    Signal_Base(double time_step, Signal_Basic_Parameters const& parameters)
        : _timer(time_step), _parameters(parameters)
    {
    }

    virtual void
    update() = 0;

    void
    update_timer()
    {
        _timer.update(1.0);
    }

    double
    time() const
    {
        return _timer.get_value();
    }

    double
    get_time_step() const
    {
        return _timer.get_time_step();
    }

    double
    get_value() const
    {
        return _value;
    }

    void
    set_parameters(Signal_Basic_Parameters const& parameters)
    {
        _parameters = parameters;
    }

    virtual void
    reset() = 0;

    void
    set_time_step(double time_step)
    {
        _timer.set_time_step(time_step);
    }

protected:
    Signal_Basic_Parameters _parameters {};

    void
    set_value(double value)
    {
        _value = value;
    }

    void
    reset_timer()
    {
        _timer.reset();
    }

private:
    double _value {};
    Integrator _timer {};
};