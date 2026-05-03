#include "integrator.h"

Integrator::Integrator(double time_step, double initial_state) : Simulation_Object_Base(time_step)
{
    set_value(initial_state);
}

void
Integrator::update(double input)
{
    set_value(get_value() + input * get_time_step());
}

void
Integrator::reset()
{
    set_value(0.0);
}