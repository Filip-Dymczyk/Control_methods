// Author: Filip Dymczyk
// Description : Derivative class.

#pragma once
#include "sim_object_base.h"

class Derivative : public SimumlationObjectBase
{
public:
    Derivative(double const time_step) : SimumlationObjectBase(time_step) {}

    void
    update(double const input) override
    {
        double const derivative = (input - _previous_value) / get_time_step();
        set_value(derivative);
        _previous_value = input;
    }
private:
    double _previous_value;
};

