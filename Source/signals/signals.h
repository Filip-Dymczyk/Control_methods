// Author: Filip Dymczyk
// Description : Basic signals.

#pragma once
#include "sim_objects/integrator.h"

// NOTE: Base class for signals.
class Signal
{
public:
    struct SignalBasicParameters
    {
        double start_time;
        double scaler;
    };

    Signal(double time_step, SignalBasicParameters const & params = {0.0, 1.0}) : _timer(time_step), _params(params) {}

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
    get_value() const
    {
        return _value;
    }

    void 
    set_parmeters(SignalBasicParameters const & params)
    {
        _params = params;
    }

    void
    reset()
    {
        _value = 0.0;
        _timer.reset();
    }
protected:
    SignalBasicParameters _params {};

    void
    set_value(double value)
    {
        _value = value;
    }
private:
    double _value {};
    Integrator _timer {};
};

// NOTE: Heaviside function - a * 1(t - t0).
class Heaviside : public Signal
{
public:
    Heaviside(double time_step, SignalBasicParameters const & params = {0.0, 1.0}) : Signal(time_step, params) {}

    void
    update() override
    {
        set_value((time() > _params.start_time) ? _params.scaler : 0.0);
        update_timer();
    }
};

// NOTE: Ramp function - a * (t - t0).
class Ramp : public Heaviside
{
public:
    Ramp(double time_step, SignalBasicParameters const & params = {0.0, 1.0}) : Heaviside(time_step, params) {}

    void
    update() override
    {
        double const input_time = time();
        Heaviside::update();
        set_value(input_time * get_value());
    }
};

// NOTE: Rectangle - a * (1(t - t0) - 1(t - t1)).
class Rectangle : public Signal
{
public:
    Rectangle(double time_step, double end_time, SignalBasicParameters const & params = {0.0, 1.0}) : Signal(time_step, params)
    {
        assert(end_time > _params.start_time);
        _end_time = end_time;
    }

    void
    update() override
    {
        set_value((time() > _params.start_time && time() < _end_time) ? _params.scaler : 0.0);
        update_timer();
    }
private:
    double _end_time {};
};

// NOTE: Sine wave - {a * sin(w * t) + b; t > t0
//                   {0.0; t <= t0.
class SineWave : public Signal
{
public:
    SineWave(double time_step, double omega, double offset, SignalBasicParameters const & params = {0.0, 1.0}) : Signal(time_step, params), _omega(omega), _offset(offset) {}

    void
    update() override
    {
        set_value((time() > _params.start_time) ? (_params.scaler * sin(_omega * time()) + _offset) : 0.0);
        update_timer();
    }
private:
    double _omega {};
    double _offset {};
};