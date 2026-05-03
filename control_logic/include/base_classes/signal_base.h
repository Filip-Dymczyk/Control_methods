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
        : m_timer(time_step), m_parameters(parameters)
    {
    }

    virtual void
    update() = 0;

    void
    update_timer()
    {
        m_timer.update(1.0);
    }

    double
    time() const
    {
        return m_timer.get_value();
    }

    double
    get_time_step() const
    {
        return m_timer.get_time_step();
    }

    double
    get_value() const
    {
        return m_value;
    }

    void
    set_parameters(Signal_Basic_Parameters const& parameters)
    {
        m_parameters = parameters;
    }

    virtual void
    reset() = 0;

    void
    set_time_step(double time_step)
    {
        m_timer.set_time_step(time_step);
    }

    virtual ~Signal_Base() = default;

protected:
    Signal_Basic_Parameters m_parameters {};

    void
    set_value(double value)
    {
        m_value = value;
    }

    void
    reset_timer()
    {
        m_timer.reset();
    }

private:
    double m_value {};
    Integrator m_timer {};
};