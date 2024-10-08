// Author: Filip Dymczyk
// Description : Basic signals.

#pragma once
#include <cstdint>
#include <math.h>
#include "integrator.h"

// NOTE: Base class for signals.
class Signal
{
public:
    struct SignalBasicParameters
    {
        double start_time {};
        double scaler {1.0};
    };

    Signal(double time_step, SignalBasicParameters const & params) : _timer(time_step), _params(params) {}

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

// NOTE: Heaviside function - a * 1(t - t0).
class Heaviside : public Signal
{
public:
    Heaviside(double time_step, SignalBasicParameters const & params = {}) : Signal(time_step, params) {}

    void
    update() override
    {
        set_value((time() >= _params.start_time) ? _params.scaler : 0.0);
        update_timer();
    }

    void
    reset() override
    {
        set_value(0.0);
        reset_timer();
    }
};

// NOTE: Ramp function - a * (t - t0).
class Ramp : public Heaviside
{
public:
    Ramp(double time_step, SignalBasicParameters const & params = {}) : Heaviside(time_step, params) {}

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
    Rectangle(double time_step, double on_time, SignalBasicParameters const & params = {}) : Signal(time_step, params)
    {
        assert(on_time > 0.0);
        _on_time = on_time;
    }

    void
    update() override
    {
        set_value(is_on() ? _params.scaler : 0.0);
        
        update_timer();
        update_on_timer();
    }

    void
    reset() override
    {
        set_value(0.0);
        reset_timer();
        _on_timer = 0.0;
    }
protected:
    void
    reset_on_timer()
    {
        _on_timer = 0.0;
    }
private:
    double _on_time {};
    double _on_timer {};

    bool
    is_on()
    {
        return (time() >= _params.start_time && _on_timer <= _on_time);
    }

    void
    update_on_timer()
    {
        _on_timer += get_time_step();
    } 
};

// NOTE: Sine wave - {a * sin(w * t) + b; t > t0
//                   {0.0; t <= t0.
class SineWave : public Signal
{
public:
    SineWave(double time_step, double omega, double offset, SignalBasicParameters const & params = {}) : Signal(time_step, params), _omega(omega), _offset(offset) {}

    void
    update() override
    {
        set_value((time() >= _params.start_time) ? (_params.scaler * sin(_omega * time()) + _offset) : 0.0);
        update_timer();
    }

    void
    reset() override
    {
        set_value(0.0);
        reset_timer();
    }
private:
    double _omega {};
    double _offset {};
};

// NOTE: Pulse wave comprising of continuous rectangles happening with given duty cycle and period.
class PulseWave : public Rectangle
{
public:
    PulseWave(double time_step, double duty_cycle, double period, SignalBasicParameters const & params = {}) : Rectangle(time_step, duty_cycle * period, params), _period(period) {}

    void
    update() override
    {
        Rectangle::update();
        if(time() >= _periods_counter * _period)
        {
            _periods_counter++;
            reset_on_timer();
        }
    }

    void
    reset() override
    {
        set_value(0.0);
        reset_timer();
        _periods_counter = 1u;
    }
private:
    std::uint32_t _periods_counter {1u};
    double _period {};
};