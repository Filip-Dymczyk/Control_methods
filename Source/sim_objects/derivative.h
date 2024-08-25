// Author: Filip Dymczyk
// Description : Derivative class.

#pragma once
#include "sim_object_base.h"

class Derivative : public SimumlationObjectBase
{
public:
    Derivative(double const timelevel) : SimumlationObjectBase(timelevel) {}

    void
    update(double const input) override
    {
        double const derivative = (input - _previous_value) / get_timelevel();
        set_value(derivative);
        _previous_value = input;
    }
private:
    double _previous_value;
};

