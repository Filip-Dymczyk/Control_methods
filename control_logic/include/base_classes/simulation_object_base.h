// Author: Filip Dymczyk
// Description : Base simulation object.

#pragma once
#include <cassert>

class Simulation_Object_Base
{
public:
    Simulation_Object_Base() : m_time_step(0.0) {}

    Simulation_Object_Base(double time_step) : m_time_step(time_step) { assert(m_time_step > 0.0); }

    virtual void
    update(double /*some input*/) = 0;

    double
    get_time_step() const
    {
        return m_time_step;
    }

    double
    get_value() const
    {
        return m_value;
    }

    virtual void
    reset() = 0;

    void
    set_time_step(double time_step)
    {
        m_time_step = time_step;
    }

    virtual ~Simulation_Object_Base() = default;

protected:
    void
    set_value(double value)
    {
        m_value = value;
    }

private:
    double m_value {};
    double m_time_step {};
};
