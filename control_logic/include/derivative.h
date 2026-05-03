// Author: Filip Dymczyk
// Description : Derivative class.

#pragma once
#include "base_classes/simulation_object_base.h"

class Derivative : public Simulation_Object_Base
{
public:
    Derivative(double time_step) : Simulation_Object_Base(time_step) {}

    void
    update(double input) override;

    void
    reset() override;

    void
    enable_filtering(bool enable);

    void
    set_filtering_coefficient(double filtering_coefficient);

private:
    bool m_enable_filtering {false};
    double m_previous_input {};
    double m_filtering_coefficient {};
};
