// Author: Filip Dymczyk
// Description : Basic signals.

#pragma once
#include <math.h>
#include <cstdint>
#include "base_classes/signal_base.h"

class No_Signal : public Signal_Base
{
public:
    No_Signal(double time_step, Signal_Basic_Parameters const& parameters) : Signal_Base(time_step, parameters) {}

    No_Signal(double time_step) : No_Signal(time_step, {}) {}

    void
    update() override
    {
        update_timer();
    }

    void
    reset() override
    {
        reset_timer();
    }
};

// NOTE: Heaviside function - a * 1(t - t0).
class Heaviside : public Signal_Base
{
public:
    Heaviside(double time_step, Signal_Basic_Parameters const& parameters) : Signal_Base(time_step, parameters) {}

    Heaviside(double time_step) : Heaviside(time_step, {}) {}

    void
    update() override
    {
        set_value((time() >= _parameters.start_time) ? _parameters.scaler : 0.0);
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
    Ramp(double time_step, Signal_Basic_Parameters const& parameters) : Heaviside(time_step, parameters) {}

    Ramp(double time_step) : Ramp(time_step, {}) {}

    void
    update() override
    {
        double const input_time = time();
        Heaviside::update();
        set_value(input_time * get_value());
    }
};

// NOTE: Rectangle - a * (1(t - t0) - 1(t - t1)).
class Rectangle : public Signal_Base
{
public:
    Rectangle(double time_step, double on_time, Signal_Basic_Parameters const& parameters)
        : Signal_Base(time_step, parameters)
    {
        assert(on_time >= 0.0);
        _on_time = on_time;
    }

    Rectangle(double time_step) : Rectangle(time_step, {}, {}) {}

    void
    update() override
    {
        set_value(is_on() ? _parameters.scaler : 0.0);

        update_timer();
        update_on_timer();
    }

    void
    reset() override
    {
        set_value(0.0);
        reset_timer();
        reset_on_timer();
    }

    void
    set_on_time(double on_time)
    {
        if(on_time < 0.0)
        {
            on_time = 0.0;
        }
        _on_time = on_time;
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
        return (time() >= _parameters.start_time && _on_timer <= _on_time);
    }

    void
    update_on_timer()
    {
        _on_timer += get_time_step();
    }
};

// NOTE: Sine wave - {a * sin(w * t) + b; t > t0
//                   {0.0; t <= t0.
class Sine_Wave : public Signal_Base
{
public:
    Sine_Wave(double time_step, double omega, double offset, Signal_Basic_Parameters const& parameters)
        : Signal_Base(time_step, parameters), _omega(omega), _offset(offset)
    {
    }

    Sine_Wave(double time_step) : Sine_Wave(time_step, {}, {}, {}) {}

    void
    update() override
    {
        set_value((time() >= _parameters.start_time) ? (_parameters.scaler * sin(_omega * time()) + _offset) : 0.0);
        update_timer();
    }

    void
    reset() override
    {
        set_value(0.0);
        reset_timer();
    }

    void
    set_omega(double omega)
    {
        if(omega < 0.0)
        {
            omega = 0.0;
        }
        _omega = omega;
    }

    void
    set_offset(double offset)
    {
        _offset = offset;
    }

private:
    double _omega {};
    double _offset {};
};

// NOTE: Pulse wave comprising of continuous rectangles happening with given duty cycle and period.
class Pulse_Wave : public Rectangle
{
public:
    Pulse_Wave(double time_step, double duty_cycle, double period, Signal_Basic_Parameters const& parameters)
        : Rectangle(time_step, duty_cycle * period, parameters), _period(period)
    {
    }

    Pulse_Wave(double time_step) : Pulse_Wave(time_step, {}, {}, {}) {}

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
        Rectangle::reset();
        set_value(0.0);
        reset_timer();
        _periods_counter = 1u;
    }

    void
    set_period(double period)
    {
        if(period < 0.0)
        {
            period = 0.0;
        }
        _period = period;
    }

    void
    set_duty_cycle(double duty_cycle)
    {
        if(duty_cycle > 1.0)
        {
            duty_cycle = 1.0;
        }
        if(duty_cycle < 0.0)
        {
            duty_cycle = 0.0;
        }
        Rectangle::set_on_time(duty_cycle * _period);
    }

private:
    std::uint32_t _periods_counter {1u};
    double _period {};
};