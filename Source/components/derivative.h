// Author: Filip Dymczyk
// Description : Derivative class.

#pragma once
#include "component_base.h"

class Derivative : public ComponentBase
{
public:
    Derivative(double timelevel) : ComponentBase(timelevel) {}

    void
    update(double input) override
    {
        double const derivative = (input - _previous_value) / get_timelevel();
        set_value(derivative);
        _previous_value = input;
    }
private:
    double _previous_value;
};

