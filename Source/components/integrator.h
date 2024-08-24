// Author: Filip Dymczyk
// Description : Integrator class.

#pragma once
#include "component_base.h"

class Integrator : public ComponentBase
{
public:
    Integrator(double timelevel) : ComponentBase(timelevel) {}

    void
    update(double input) override
    {
        set_value(get_value() + input * get_timelevel());
    }
};

