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

        if(_enable_filtering)
        {
            input = _filtering_coefficient * _previous_input + (1.0 - _filtering_coefficient) * input;
        }

        double const derivative = (input - _previous_input) / get_time_step();
        set_value(derivative);

        _previous_input = input;
    }

    void
    reset() override
    {
        set_value(0.0);
        _previous_input = 0.0;
    }

    void
    enable_filtering(bool enable)
    {
        _enable_filtering = enable;
    }

    void
    set_filtering_coefficient(double filtering_coefficient)
    {
        assert(filtering_coefficient > 0.0);
        assert(filtering_coefficient < 1.0);

        _filtering_coefficient = filtering_coefficient;
    }

private:
    bool _enable_filtering {false};
    double _previous_input {};
    double _filtering_coefficient {};
};
