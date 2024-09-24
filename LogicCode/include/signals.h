// Author: Filip Dymczyk
// Description : Basic signals.

#pragma once
#include <cstdint>
#include <math.h>
#include "base_classes/signal_base.h"

// NOTE: Heaviside function - a * 1(t - t0).
class Heaviside : public SignalBase
{
public:
    Heaviside(double time_step, SignalBasicParameters const & params = {}) : SignalBase(time_step, params) {}

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
class Rectangle : public SignalBase
{
public:
    Rectangle(double time_step, double on_time, SignalBasicParameters const & params = {}) : SignalBase(time_step, params)
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
class SineWave : public SignalBase
{
public:
    SineWave(double time_step, double omega, double offset, SignalBasicParameters const & params = {}) : SignalBase(time_step, params), _omega(omega), _offset(offset) {}

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