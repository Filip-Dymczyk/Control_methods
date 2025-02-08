// Author: Filip Dymczyk
// Description : Derivative class.

#pragma once
#include "base_classes/simulation_object_base.h"

class Derivative : public Simulation_Object_Base
{
public:
    Derivative(double time_step) : Simulation_Object_Base(time_step) {}

    void
    update(double input) override
    {
        assert(get_time_step() > 0.0);
        double const derivative = (input - _previous_value) / get_time_step();
        set_value(derivative);
        _previous_value = input;
    }

    void
    reset() override
    {
        set_value(0.0);
        _previous_value = 0.0;
    }

private:
    double _previous_value {};
};
