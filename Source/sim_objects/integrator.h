// Author: Filip Dymczyk
// Description : Integrator class.

#pragma once
#include "sim_object_base.h"

class Integrator : public SimumlationObjectBase
{
public:
    Integrator() : SimumlationObjectBase() {}
    Integrator(double const time_step, double const initial_state = 0) : SimumlationObjectBase(time_step) 
    {
        set_value(initial_state);
    }

    void
    update(double const input) override
    {
        set_value(get_value() + input * get_time_step());
    }
};

