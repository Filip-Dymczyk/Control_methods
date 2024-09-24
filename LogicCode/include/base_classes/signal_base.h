// Author: Filip Dymczyk
// Description : Base class for signals.

#pragma once
#include "integrator.h"

class SignalBase
{
public:
    struct SignalBasicParameters
    {
        double start_time {};
        double scaler {1.0};
    };

    SignalBase(double time_step, SignalBasicParameters const & params) : _timer(time_step), _params(params) {}

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
    set_parmeters(SignalBasicParameters const & params)
    {
        _params = params;
    }

    virtual void
    reset() = 0;

protected:
    SignalBasicParameters _params {};

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