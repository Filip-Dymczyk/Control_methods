// Author: Filip Dymczyk
// Description : Integrator class.

#pragma once
#include "base_classes/simulation_object_base.h"

class Integrator : public Simulation_Object_Base
{
public:
    Integrator() : Simulation_Object_Base() {}

    Integrator(double time_step, double initial_state = 0.0);

    void
    update(double input) override;

    void
    reset() override;
};
