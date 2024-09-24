// Author: Filip Dymczyk
// Description : Integrator class.

#pragma once
#include "base_classes/sim_object_base.h"

class Integrator : public SimumlationObjectBase
{
public:
    Integrator() : SimumlationObjectBase() {}
    Integrator(double time_step, double initial_state = 0.0) : SimumlationObjectBase(time_step) 
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

