// Author: Filip Dymczyk
// Description : Integrator class.

#pragma once
#include "base_classes/simulation_object_base.h"

class Integrator : public Simulation_Object_Base
{
public:
    Integrator() : Simulation_Object_Base() {}
    Integrator(double time_step, double initial_state = 0.0) : Simulation_Object_Base(time_step)
    {
        set_value(initial_state);
    }

    void
    update(double input) override
    {
        set_value(get_value() + input * get_time_step());
    }

    void
    reset() override
    {
        set_value(0.0);
    }
};
