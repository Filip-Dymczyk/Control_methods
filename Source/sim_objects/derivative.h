// Author: Filip Dymczyk
// Description : Derivative class.

#pragma once
#include "sim_object_base.h"
#include <assert.h>

class Derivative : public SimumlationObjectBase
{
public:
    Derivative(double time_step) : SimumlationObjectBase(time_step) {}

    void
    update(double input) override
    {
        assert(get_time_step() > 0.0);
        double const derivative = (input - _previous_value) / get_time_step();
        set_value(derivative);
        _previous_value = input;
    }
private:
    double _previous_value;
};

